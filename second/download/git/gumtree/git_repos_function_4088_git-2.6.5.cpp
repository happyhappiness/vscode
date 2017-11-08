static inline void rlw_xor_run_bit(eword_t *word)
{
	if (*word & 1) {
		*word &= (eword_t)(~1);
	} else {
		*word |= (eword_t)1;
	}
}