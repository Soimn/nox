typedef union X_i128
{
  struct
  {
    X_u64 lo;
    X_u64 hi;
  };

  X_u32 e[4];
} X_i128;

// TODO: Instructions only set status flag bits, clearing must be manually done before
//       passing the flag pointer to an instruction
typedef enum X_I128_Status_Flag
{
  X_I128Status_Overflow = 1,
  X_I128Status_Carry    = 2,
} X_I128_Status_Flag

X_i128
X_I128_AddU64(X_i128 a, X_u64 b, X_I128_Status_Flag* status)
{
  X_i128 result;

  X_u8 c1 = _addcarry_u64(0, a.lo, b, &result.lo);
  X_u8 c2 = _addcarry_u64(c1, a.hi, 0, &result.hi);

  if (c2 != 0)                                    *status |= X_I128Status_Carry;
  if ((X_i64)a.hi >= 0 && (x_i64)(result.hi) < 0) *status |= X_I128Status_Overflow;
}

X_i128
X_I128_Add(X_i128 a, X_i128 b, X_I128_Status_Flag* status)
{
  X_i128 result;

  X_u8 c1 = _addcarry_u64(0, a.lo, b.lo, &result.lo);
  X_u8 c2 = _addcarry_u64(c1, a.hi, b.hi, &result.hi);

  if (c2 != 0)                                                    *status |= X_I128Status_Carry;
  if ((X_i64)(a.hi ^ b.hi) >= 0 && (x_i64)(a.hi ^ result.hi) < 0) *status |= X_I128Status_Overflow; // NOTE: extended from https://graphics.stanford.edu/~seander/bithacks.html#DetectOppositeSigns
}

X_i128
X_I128_Mul(X_i128 a, X_i128 b, X_I128_Status_Flag* status)
{
  /* NOTE:
    (2^64 - 1)(2^64 - 1) = (2^128 - 2^64 - 2^64 + 1) = (2^128 - 2^65 + 1) = (2^128 - 1 - 2^65 + 2)
    = (0xFFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF - 2^65 + 2)
    = (0xFFFF FFFF FFFF FFFD FFFF FFFF FFFF FFFF + 2)
    = (0xFFFF FFFF FFFF FFFD FFFF FFFF FFFF FFFF + 1 + 1)
    = (0xFFFF FFFF FFFF FFFE 0000 0000 0000 0000 + 1)
    = (0xFFFF FFFF FFFF FFFE 0000 0000 0000 0001)
    = 2^127 +..+ 2^65 + 1

    (a1x + a0)(b1x + b0) = a1b1x^2 + a1b0x + a0b1x + a0b0
  */

  X_u64 a0 = a.lo;
  X_u64 a1 = a.hi;
  X_u64 b0 = b.lo;
  X_u64 b1 = b.hi;

  X_bool should_flip_sign = X_false;
  if ((X_i64)a1 < 0)
  {
    _addcarry_u64(_addcarry_u64(1, ~a0, 0, &a0), ~a1, 0, &a1);
    should_flip_sign = !should_flip_sign;
  }

  if ((X_i64)b1 < 0)
  {
    _addcarry_u64(_addcarry_u64(1, ~b0, 0, &b0), ~b1, 0, &b1);
    should_flip_sign = !should_flip_sign;
  }

  X_u64 a0b0_hi, a0b1_hi, a1b0_hi;
  X_u64 a0b0_lo = X_umul128(a0, b0, &a0b0_hi);
  X_u64 a0b1_lo = X_umul128(a0, b1, &a0b1_hi);
  X_u64 a1b0_lo = X_umul128(a1, b0, &a1b0_hi);

  X_i128 result;
  result.lo = a0b0_lo;
  X_u8 c1 = _addcarry_u64(0, a0b0_hi, a0b1_lo, &result.hi);
  X_u8 c2 = _addcarry_u64(0, result.hi, a1b0_lo, &result.hi);

  if (should_flip_sign) result = X_I128_Neg(result);

  X_NOT_IMPLEMENTED; // TODO: update status

  return result;
}
