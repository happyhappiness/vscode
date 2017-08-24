{
	struct lzx_dec *ds = strm->ds;
	unsigned char *b, *end;

	if (!ds->translation || size <= 10)
		return;
	b = p;
	end = b + size - 10;
	while (b < end && (b = memchr(b, 0xE8, end - b)) != NULL) {
		size_t i = b - (unsigned char *)p;
		int32_t cp, displacement, value;

		cp = (int32_t)(offset + (uint32_t)i);
		value = archive_le32dec(&b[1]);
		if (value >= -cp && value < (int32_t)ds->translation_size) {
			if (value >= 0)
				displacement = value - cp;
			else
				displacement = value + ds->translation_size;
			archive_le32enc(&b[1], (uint32_t)displacement);
		}
		b += 5;
	}
}