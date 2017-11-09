void free_commit_buffer(struct commit *commit)
{
	struct commit_buffer *v = buffer_slab_peek(&buffer_slab, commit);
	if (v) {
		FREE_AND_NULL(v->buffer);
		v->size = 0;
	}
}