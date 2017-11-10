static inline void rlw_set_run_bit(eword_t *word, int b)
{
	if (b) {
		*word |= (eword_t)1;
	} else {
		*word &= (eword_t)(~1);
	}
}