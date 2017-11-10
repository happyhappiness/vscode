void ewah_pool_free(struct ewah_bitmap *self)
{
	if (self == NULL)
		return;

	if (bitmap_pool_size == BITMAP_POOL_MAX ||
		self->alloc_size == 0) {
		ewah_free(self);
		return;
	}

	ewah_clear(self);
	bitmap_pool[bitmap_pool_size++] = self;
}