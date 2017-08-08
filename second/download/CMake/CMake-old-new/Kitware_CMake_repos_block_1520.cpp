{
	static const char _ver[] = "WARC/1.0\r\n";
	static const char *_typ[LAST_WT] = {
		NULL, "warcinfo", "metadata", "resource", NULL
	};
	char std_uuid[48U];

	if (hdr.type == WT_NONE || hdr.type > WT_RSRC) {
		/* brilliant, how exactly did we get here? */
		return -1;
	}

	archive_strcpy(tgt, _ver);

	archive_string_sprintf(tgt, "WARC-Type: %s\r\n", _typ[hdr.type]);

	if (hdr.tgturi != NULL) {
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

	/* record time is usually when the http is sent off,
	 * just treat the archive writing as such for a moment */
	xstrftime(tgt, "WARC-Date: %Y-%m-%dT%H:%M:%SZ\r\n", hdr.rtime);

	/* while we're at it, record the mtime */
	xstrftime(tgt, "Last-Modified: %Y-%m-%dT%H:%M:%SZ\r\n", hdr.mtime);

	if (hdr.recid == NULL) {
		/* generate one, grrrr */
		warc_uuid_t u;

		_gen_uuid(&u);
		/* Unfortunately, archive_string_sprintf does not
		 * handle the minimum number following '%'.
		 * So we have to use snprintf function here instead
		 * of archive_string_snprintf function. */
#if defined(_WIN32) && !defined(__CYGWIN__) && !( defined(_MSC_VER) && _MSC_VER >= 1900)
#define snprintf _snprintf
#endif
		snprintf(
			std_uuid, sizeof(std_uuid),
			"<urn:uuid:%08x-%04x-%04x-%04x-%04x%08x>",
			u.u[0U],
			u.u[1U] >> 16U, u.u[1U] & 0xffffU,
			u.u[2U] >> 16U, u.u[2U] & 0xffffU,
			u.u[3U]);
		hdr.recid = std_uuid;
	}

	/* record-id is mandatory, fingers crossed we won't fail */
	archive_string_sprintf(tgt, "WARC-Record-ID: %s\r\n", hdr.recid);

	if (hdr.cnttyp != NULL) {
		archive_string_sprintf(tgt, "Content-Type: %s\r\n", hdr.cnttyp);
	}

	/* next one is mandatory */
	archive_string_sprintf(tgt, "Content-Length: %ju\r\n", (uintmax_t)hdr.cntlen);
	/**/
	archive_strncat(tgt, "\r\n", 2);

	return (archive_strlen(tgt) >= tsz)? -1: (ssize_t)archive_strlen(tgt);
}