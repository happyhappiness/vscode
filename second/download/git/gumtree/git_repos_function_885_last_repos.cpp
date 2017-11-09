void unuse_commit_buffer(const struct commit *commit, const void *buffer)
{
	struct commit_buffer *v = buffer_slab_peek(&buffer_slab, commit);
	if (!(v && v->buffer == buffer))
		free((void *)buffer);
}