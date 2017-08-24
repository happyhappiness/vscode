{
		archive_strcat(str, " sha1digest=");
		strappend_bin(str, reg->buf_sha1, sizeof(reg->buf_sha1));
	}