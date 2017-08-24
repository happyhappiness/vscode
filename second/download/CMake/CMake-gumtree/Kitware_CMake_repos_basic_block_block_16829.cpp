{
		archive_strcat(str, " sha256digest=");
		strappend_bin(str, reg->buf_sha256, sizeof(reg->buf_sha256));
	}