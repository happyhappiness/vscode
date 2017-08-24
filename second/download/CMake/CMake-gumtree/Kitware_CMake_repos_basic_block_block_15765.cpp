{
		if (copy_length > GNUTAR_uname_size)
			copy_length = GNUTAR_uname_size;
		memcpy(h + GNUTAR_uname_offset, p, copy_length);
	}