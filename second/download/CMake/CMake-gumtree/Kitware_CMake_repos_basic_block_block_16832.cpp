{
		archive_strcat(str, " md5digest=");
		strappend_bin(str, reg->buf_md5, sizeof(reg->buf_md5));
	}