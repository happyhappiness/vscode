{
		/* check if there's a xyz:// */
		static const char _uri[] = "";
		static const char _fil[] = "file://";
		const char *u;
		char *chk = strchr(hdr.tgturi, ':');

		if (chk != NULL && chk[1U] == '/' && chk[2U] == '/') {
			/* yep, it's definitely a URI */
			u = _uri;
		} else {
			/* hm, best to prepend file:// then */
			u = _fil;
		}
		archive_string_sprintf(tgt,
			"WARC-Target-URI: %s%s\r\n", u, hdr.tgturi);
	}