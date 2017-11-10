int ewah_read_mmap(struct ewah_bitmap *self, void *map, size_t len)
{
	uint8_t *ptr = map;
	size_t i;

	self->bit_size = get_be32(ptr);
	ptr += sizeof(uint32_t);

	self->buffer_size = self->alloc_size = get_be32(ptr);
	ptr += sizeof(uint32_t);

	self->buffer = ewah_realloc(self->buffer,
		self->alloc_size * sizeof(eword_t));

	if (!self->buffer)
		return -1;

	/*
	 * Copy the raw data for the bitmap as a whole chunk;
	 * if we're in a little-endian platform, we'll perform
	 * the endianness conversion in a separate pass to ensure
	 * we're loading 8-byte aligned words.
	 */
	memcpy(self->buffer, ptr, self->buffer_size * sizeof(uint64_t));
	ptr += self->buffer_size * sizeof(uint64_t);

	for (i = 0; i < self->buffer_size; ++i)
		self->buffer[i] = ntohll(self->buffer[i]);

	self->rlw = self->buffer + get_be32(ptr);

	return (3 * 4) + (self->buffer_size * 8);
}