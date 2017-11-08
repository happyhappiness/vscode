static int rlw_get_run_bit(const eword_t *word)
{
	return *word & (eword_t)1;
}