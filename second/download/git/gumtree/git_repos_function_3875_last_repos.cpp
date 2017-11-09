static void free_mmfile(mmfile_t *f)
{
	free(f->ptr);
}