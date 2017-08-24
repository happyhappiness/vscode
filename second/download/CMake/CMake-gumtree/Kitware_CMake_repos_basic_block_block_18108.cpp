{
		uint32_t copy_pos;
		uint32_t copy_size;

		// The bigger the dictionary, the more rare this
		// case occurs. We need to "wrap" the dict, thus
		// we might need two memcpy() to copy all the data.
		assert(dict->full == dict->size);
		copy_pos = dict->pos - distance - 1 + dict->size;
		copy_size = dict->size - copy_pos;

		if (copy_size < left) {
			memmove(dict->buf + dict->pos, dict->buf + copy_pos,
					copy_size);
			dict->pos += copy_size;
			copy_size = left - copy_size;
			memcpy(dict->buf + dict->pos, dict->buf, copy_size);
			dict->pos += copy_size;
		} else {
			memmove(dict->buf + dict->pos, dict->buf + copy_pos,
					left);
			dict->pos += left;
		}
	}