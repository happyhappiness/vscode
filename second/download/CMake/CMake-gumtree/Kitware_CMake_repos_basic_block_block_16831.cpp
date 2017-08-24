{
		archive_strcat(str, " rmd160digest=");
		strappend_bin(str, reg->buf_rmd160, sizeof(reg->buf_rmd160));
	}