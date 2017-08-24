{
		archive_strcat(str, " sha384digest=");
		strappend_bin(str, reg->buf_sha384, sizeof(reg->buf_sha384));
	}