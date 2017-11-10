int ewah_serialize_native(struct ewah_bitmap *self, int fd)
{
	uint32_t write32;
	size_t to_write = self->buffer_size * 8;

	/* 32 bit -- bit size for the map */
	write32 = (uint32_t)self->bit_size;
	if (write(fd, &write32, 4) != 4)
		return -1;

	/** 32 bit -- number of compressed 64-bit words */
	write32 = (uint32_t)self->buffer_size;
	if (write(fd, &write32, 4) != 4)
		return -1;

	if (write(fd, self->buffer, to_write) != to_write)
		return -1;

	/** 32 bit -- position for the RLW */
	write32 = self->rlw - self->buffer;
	if (write(fd, &write32, 4) != 4)
		return -1;

	return (3 * 4) + to_write;
}