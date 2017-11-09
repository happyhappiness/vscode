int ewah_serialize(struct ewah_bitmap *self, int fd)
{
	return ewah_serialize_to(self, write_helper, (void *)(intptr_t)fd);
}