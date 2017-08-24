{
		if (strlen(p) > GNUTAR_gname_size)
			copy_length = GNUTAR_gname_size;
		memcpy(h + GNUTAR_gname_offset, p, copy_length);
	}