static inline void buffer_push(struct ewah_bitmap *self, eword_t value)
{
	if (self->buffer_size + 1 >= self->alloc_size)
		buffer_grow(self, self->buffer_size * 3 / 2);

	self->buffer[self->buffer_size++] = value;
}