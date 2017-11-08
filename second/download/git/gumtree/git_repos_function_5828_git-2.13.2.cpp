static inline uint32_t ptr_to_mark(void * mark)
{
	return (uint32_t *)mark - (uint32_t *)NULL;
}