{
	if ((uint32_t)(rc->low) < (uint32_t)(0xFF000000)
			|| (uint32_t)(rc->low >> 32) != 0) {
		do {
			if (*out_pos == out_size)
				return true;

			out[*out_pos] = rc->cache + (uint8_t)(rc->low >> 32);
			++*out_pos;
			rc->cache = 0xFF;

		} while (--rc->cache_size != 0);

		rc->cache = (rc->low >> 24) & 0xFF;
	}

	++rc->cache_size;
	rc->low = (rc->low & 0x00FFFFFF) << RC_SHIFT_BITS;

	return false;
}