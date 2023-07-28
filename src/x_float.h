typedef union X_F16_Bits
{
  X_u16 bits;
} X_F16_Bits;

#define X_F16_SGN_MASK 0x8000
#define X_F16_EXP_BITS 5
#define X_F16_EXP_MASK 0x7C00
#define X_F16_EXP_BIAS 15
#define X_F16_EXP_EMAX 15
#define X_F16_EXP_EMIN -14
#define X_F16_MAN_BITS 10
#define X_F16_MAN_MASK 0x03FF

typedef union X_F32_Bits
{
  X_u32 bits;
  X_f32 f;
} X_F32_Bits;

#define X_F32_SGN_MASK 0x80000000UL
#define X_F32_EXP_BITS 8
#define X_F32_EXP_MASK 0x7F800000UL
#define X_F32_EXP_BIAS 127
#define X_F32_EXP_EMAX 127
#define X_F32_EXP_EMIN -126
#define X_F32_MAN_BITS 23
#define X_F32_MAN_MASK 0x007FFFFFUL

typedef union X_F64_Bits
{
  X_u64 bits;
  X_f64 f;
} X_F64_Bits;

#define X_F64_SGN_MASK 0x8000000000000000ULL
#define X_F64_EXP_BITS 11
#define X_F64_EXP_MASK 0x7FF0000000000000ULL
#define X_F64_EXP_BIAS 1023
#define X_F64_EXP_EMAX 1023
#define X_F64_EXP_EMIN -1022
#define X_F64_MAN_BITS 52
#define X_F64_MAN_MASK 0x000FFFFFFFFFFFFFULL

X_f32
X_F16_ToF32(X_F16_Bits f)
{
  X_f32 result;

  X_NOT_IMPLEMENTED;

  return result;
}

X_F16_Bits
X_F16_FromF32(X_f32 f)
{
  X_F16_Result result;

  X_NOT_IMPLEMENTED;

  return result;
}
