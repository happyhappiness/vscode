{
		archive_strcat(str, " sha512digest=");
		strappend_bin(str, reg->buf_sha512, sizeof(reg->buf_sha512));
	}