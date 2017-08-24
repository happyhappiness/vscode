{
		p = __archive_read_filter_ahead(filter, len + 2, &avail);
		if (p == NULL)
			return (0);
#if 0
	int hcrc = ((int)p[len + 1] << 8) | (int)p[len];
	int crc = /* XXX TODO: Compute header CRC. */;
	if (crc != hcrc)
		return (0);
	bits += 16;
#endif
		len += 2;
	}