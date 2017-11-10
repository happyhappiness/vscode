void set_commit_buffer(struct commit *commit, void *buffer, unsigned long size)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	v->buffer = buffer;
	v->size = size;
}