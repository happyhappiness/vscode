void SAFE_FREE(void *mem)
{
	if (mem)
		free(mem);
}