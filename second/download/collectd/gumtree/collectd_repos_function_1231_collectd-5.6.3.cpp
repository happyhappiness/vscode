static double ntohf(tFloat p_float) {
/* Convert tFloat in Network-bit-order to double in host-bit-order */

#define FLOAT_EXP_BITS 7
#define FLOAT_EXP_MIN (-(1 << (FLOAT_EXP_BITS - 1)))
#define FLOAT_EXP_MAX (-FLOAT_EXP_MIN - 1)
#define FLOAT_COEF_BITS ((int)sizeof(int32_t) * 8 - FLOAT_EXP_BITS)
#define FLOAT_COEF_MIN (-(1 << (FLOAT_COEF_BITS - 1)))
#define FLOAT_COEF_MAX (-FLOAT_COEF_MIN - 1)

  int32_t exp, coef;
  uint32_t uval;

  uval = ntohl(p_float.value);
  exp = (uval >> FLOAT_COEF_BITS) - FLOAT_COEF_BITS;
  if (exp >= 1 << (FLOAT_EXP_BITS - 1))
    exp -= 1 << FLOAT_EXP_BITS;

  /* coef = (x << FLOAT_EXP_BITS) >> FLOAT_EXP_BITS; */
  coef = uval % (1U << FLOAT_COEF_BITS);
  if (coef >= 1 << (FLOAT_COEF_BITS - 1))
    coef -= 1 << FLOAT_COEF_BITS;

  return coef * pow(2.0, exp);
}