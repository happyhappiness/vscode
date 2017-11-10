static inline eword_t rlw_get_literal_words(const eword_t *word)
{
	return *word >> (1 + RLW_RUNNING_BITS);
}