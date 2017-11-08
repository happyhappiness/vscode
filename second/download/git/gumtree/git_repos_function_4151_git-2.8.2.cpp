int bitmap_equals(struct bitmap *self, struct bitmap *other)
{
	struct bitmap *big, *small;
	size_t i;

	if (self->word_alloc < other->word_alloc) {
		small = self;
		big = other;
	} else {
		small = other;
		big = self;
	}

	for (i = 0; i < small->word_alloc; ++i) {
		if (small->words[i] != big->words[i])
			return 0;
	}

	for (; i < big->word_alloc; ++i) {
		if (big->words[i] != 0)
			return 0;
	}

	return 1;
}