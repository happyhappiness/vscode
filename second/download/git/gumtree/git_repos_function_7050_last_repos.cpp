static inline void
bitset_mask (bitset_t dest, const bitset_t src)
{
  int bitset_i;
  for (bitset_i = 0; bitset_i < BITSET_WORDS; ++bitset_i)
    dest[bitset_i] &= src[bitset_i];
}