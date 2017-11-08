struct ewah_bitmap *ewah_new(void)
{
	struct ewah_bitmap *self;

	self = ewah_malloc(sizeof(struct ewah_bitmap));
	if (self == NULL)
		return NULL;

	self->buffer = ewah_malloc(32 * sizeof(eword_t));
	self->alloc_size = 32;

	ewah_clear(self);
	return self;
}