const void *get_cached_commit_buffer(const struct commit *commit, unsigned long *sizep)
{
	struct commit_buffer *v = buffer_slab_peek(&buffer_slab, commit);
	if (!v) {
		if (sizep)
			*sizep = 0;
		return NULL;
	}
	if (sizep)
		*sizep = v->size;
	return v->buffer;
}