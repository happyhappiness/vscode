void ewah_free(struct ewah_bitmap *self)
{
	if (!self)
		return;

	if (self->alloc_size)
		free(self->buffer);

	free(self);
}