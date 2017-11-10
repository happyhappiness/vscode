void free_commit_buffer(struct commit *commit)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	free(v->buffer);
	v->buffer = NULL;
	v->size = 0;
}