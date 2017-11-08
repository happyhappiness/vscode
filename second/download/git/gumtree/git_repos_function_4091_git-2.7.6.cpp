static inline eword_t rlw_get_running_len(const eword_t *word)
{
	return (*word >> 1) & RLW_LARGEST_RUNNING_COUNT;
}