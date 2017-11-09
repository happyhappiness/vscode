uint32_t ewah_checksum(struct ewah_bitmap *self)
{
	const uint8_t *p = (uint8_t *)self->buffer;
	uint32_t crc = (uint32_t)self->bit_size;
	size_t size = self->buffer_size * sizeof(eword_t);

	while (size--)
		crc = (crc << 5) - crc + (uint32_t)*p++;

	return crc;
}