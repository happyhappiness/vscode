	if (ver != w->pver) {
		/* stringify this entry's version */
		archive_string_sprintf(&w->sver,
			"WARC/%u.%u", ver / 10000, ver % 10000);
		/* remember the version */
		w->pver = ver;
	}
