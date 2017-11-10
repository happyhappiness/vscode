unsigned long xdl_hash_record(char const **data, char const *top, long flags)
{
	unsigned long hash = 5381;
	unsigned long a = 0, mask = 0;
	char const *ptr = *data;
	char const *end = top - sizeof(unsigned long) + 1;

	if (flags & XDF_WHITESPACE_FLAGS)
		return xdl_hash_record_with_whitespace(data, top, flags);

	ptr -= sizeof(unsigned long);
	do {
		hash += hash << 5;
		hash ^= a;
		ptr += sizeof(unsigned long);
		if (ptr >= end)
			break;
		a = *(unsigned long *)ptr;
		/* Do we have any '\n' bytes in this word? */
		mask = has_zero(a ^ NEWLINEBYTES);
	} while (!mask);

	if (ptr >= end) {
		/*
		 * There is only a partial word left at the end of the
		 * buffer. Because we may work with a memory mapping,
		 * we have to grab the rest byte by byte instead of
		 * blindly reading it.
		 *
		 * To avoid problems with masking in a signed value,
		 * we use an unsigned char here.
		 */
		const char *p;
		for (p = top - 1; p >= ptr; p--)
			a = (a << 8) + *((const unsigned char *)p);
		mask = has_zero(a ^ NEWLINEBYTES);
		if (!mask)
			/*
			 * No '\n' found in the partial word.  Make a
			 * mask that matches what we read.
			 */
			mask = 1UL << (8 * (top - ptr) + 7);
	}

	/* The mask *below* the first high bit set */
	mask = (mask - 1) & ~mask;
	mask >>= 7;
	hash += hash << 5;
	hash ^= a & mask;

	/* Advance past the last (possibly partial) word */
	ptr += count_masked_bytes(mask);

	if (ptr < top) {
		assert(*ptr == '\n');
		ptr++;
	}

	*data = ptr;

	return hash;
}