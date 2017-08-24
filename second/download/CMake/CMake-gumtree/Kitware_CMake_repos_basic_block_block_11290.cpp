{
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