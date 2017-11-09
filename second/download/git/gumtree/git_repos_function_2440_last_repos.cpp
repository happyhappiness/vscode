static void normalize_file(mmfile_t *mm, const char *path)
{
	struct strbuf strbuf = STRBUF_INIT;
	if (renormalize_buffer(&the_index, path, mm->ptr, mm->size, &strbuf)) {
		free(mm->ptr);
		mm->size = strbuf.len;
		mm->ptr = strbuf_detach(&strbuf, NULL);
	}
}