
/* Set the value of the register at position 'regnum' to 'val'.
 * 'p' is an array of unsigned bytes. */
#define HLL_SET_REGISTER(val,p,regnum) do { \
    int _byte = regnum*REDIS_HLL_BITS/8; \
    int _leftshift = regnum*REDIS_HLL_BITS&7; \
    int _rightshift = 8 - _leftshift; \
    unsigned int m1 = 255, m2 = (1<<REDIS_HLL_BITS)-1; \
    p[byte] &= m1 << _rightshift; \
    p[byte] |= val >> _leftshift; \
    p[byte+1] &= ~(m2 << _rightshift); \
    p[byte+1] |= val << _rightshift; \
} while(0)

/* ========================= HyperLogLog algorithm  ========================= */

/* ========================== HyperLogLog commands ========================== */

