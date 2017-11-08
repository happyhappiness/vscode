static inline void buffer_grow(struct ewah_bitmap *self, size_t new_size)
{
	size_t rlw_offset = (uint8_t *)self->rlw - (uint8_t *)self->buffer;

	if (self->alloc_size >= new_size)
		return;

	self->alloc_size = new_size;
	self->buffer = ewah_realloc(self->buffer,
		self->alloc_size * sizeof(eword_t));
	self->rlw = self->buffer + (rlw_offset / sizeof(eword_t));
}