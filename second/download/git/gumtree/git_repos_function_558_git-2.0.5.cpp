const void *get_cached_commit_buffer(const struct commit *commit, unsigned long *sizep)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	if (sizep)
		*sizep = v->size;
	return v->buffer;
}