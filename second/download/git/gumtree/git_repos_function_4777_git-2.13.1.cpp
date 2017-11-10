struct ewah_bitmap *ewah_new(void)
{
	struct ewah_bitmap *self;

	self = xmalloc(sizeof(struct ewah_bitmap));
	self->alloc_size = 32;
	ALLOC_ARRAY(self->buffer, self->alloc_size);

	ewah_clear(self);
	return self;
}