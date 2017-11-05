void free_commit_buffer(struct commit *commit)
{
	struct commit_buffer *v = buffer_slab_peek(&buffer_slab, commit);
	if (v) {
		free(v->buffer);
		v->buffer = NULL;
		v->size = 0;
	}
}