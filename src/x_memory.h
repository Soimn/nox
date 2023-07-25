X_umm
X_AlignDown(X_umm n, X_umm alignment)
{
  X_ASSERT(alignment != 0 && ((alignment-1) & alignment) == 0);
  return n & (alignment-1);
}

X_umm
X_AlignUp(X_umm n, X_umm alignment)
{
  X_ASSERT(alignment != 0 && ((alignment-1) & alignment) == 0);
  return (n + (alignment-1)) & (alignment-1);
}

void*
X_Align(void* ptr, X_umm alignment)
{
  X_ASSERT(alignment != 0 && ((alignment-1) & alignment) == 0);
  return (void*)(((X_umm)ptr + (alignment-1)) & (alignment-1));
}

typedef struct X_Arena
{
  X_umm commit_pace;
  X_umm cursor;
  X_umm watermark;
  X_u8 content[];
} X_Arena;

typedef X_umm X_Arena_Marker;

X_Arena*
X_Arena_Create(X_umm reserve_size, X_umm commit_pace)
{
  X_umm page_size = X_GetPageSize();

  commit_pace = X_AlignUp(commit_pace, page_size);
  X_ASSERT(commit_pace > sizeof(X_Arena));

  X_Arena* arena = X_ReserveMemory(reserve_size);
  X_CommitMemory(arena, commit_pace);
  
  *arena = (X_Arena){
    .cursor      = 0,
    .commit_pace = commit_pace,
    .watermark   = commit_pace - sizeof(X_Arena),
  };

  return arena;
}

void
X_Arena_Destroy(X_Arena* arena)
{
  X_FreeMemory(arena);
}

void*
X_Arena_Push(X_Arena* arena, X_umm size, X_umm alignment)
{
  X_ASSERT(alignment < X_GetPageSize());

  X_u8* result = X_Align(arena->content + arena->cursor, alignment);

  X_ASSERT(size <= X_UMM_MAX - (result - arena->content));
  arena->cursor = (result + size) - arena->content;

  if (arena->cursor > arena->watermark)
  {
    X_umm to_commit = X_AlignUp(arena->cursor - arena->watermark, arena->commit_pace);
    X_CommitMemory(arena->content + arena->watermark, to_commit);
    arena->watermark += to_commit;
  }

  return result;
}

void
X_Arena_Pop(X_Arena* arena, X_umm bytes)
{
  X_ASSERT(arena->cursor >= bytes);
  arena->cursor -= bytes;
}

void
X_Arena_PopToMarker(X_Arena* arena, X_Arena_Marker marker)
{
  arena->cursor = marker;
}

X_Arena_Marker
X_Arena_GetMarker(X_Arena* arena)
{
  return arena->cursor;
}

void
X_Arena_Clear(X_Arena* arena)
{
  arena->cursor = 0;
}
