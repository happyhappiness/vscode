{
		if (copy_length > GNUTAR_linkname_size)
			copy_length = GNUTAR_linkname_size;
		memcpy(h + GNUTAR_linkname_offset, gnutar->linkname,
		    copy_length);
	}