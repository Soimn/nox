typedef union X_i128
{
  struct
  {
    X_u64 lo;
    X_u64 hi;
  };

  X_u32 e[4];
} X_i128;
