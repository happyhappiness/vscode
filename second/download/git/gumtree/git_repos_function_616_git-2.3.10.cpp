const void *detach_commit_buffer(struct commit *commit, unsigned long *sizep)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	void *ret;

	ret = v->buffer;
	if (sizep)
		*sizep = v->size;

	v->buffer = NULL;
	v->size = 0;
	return ret;
}