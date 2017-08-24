(i = 0; i < num; i++) {
		if (d->defineds[i]) {
			if ((p = header_bytes(a, 4)) == NULL)
				return (-1);
			d->digests[i] = archive_le32dec(p);
		}
	}