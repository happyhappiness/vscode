{
		size_t copy_size;

		// Control byte: Indicate uncompressed chunk, of which
		// the first resets the dictionary.
		out[(*out_pos)++] = control;
		control = 0x02; // No dictionary reset

		// Size of the uncompressed chunk
		copy_size = my_min(in_size - in_pos, LZMA2_CHUNK_MAX);
		out[(*out_pos)++] = (copy_size - 1) >> 8;
		out[(*out_pos)++] = (copy_size - 1) & 0xFF;

		// The actual data
		assert(*out_pos + copy_size <= out_size);
		memcpy(out + *out_pos, in + in_pos, copy_size);

		in_pos += copy_size;
		*out_pos += copy_size;
	}