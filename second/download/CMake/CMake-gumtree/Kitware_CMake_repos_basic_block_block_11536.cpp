{
		if (!memcmp(iso9660->null, h + offset, sizeof(iso9660->null)))
			return (0);
		offset += sizeof(iso9660->null);
		bytes -= sizeof(iso9660->null);
	}