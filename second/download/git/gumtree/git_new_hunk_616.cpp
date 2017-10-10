	else {
		char *hex = oid_to_hex(oid);
		if (abbrev < 0)
			abbrev = FALLBACK_DEFAULT_ABBREV;
		if (abbrev > GIT_SHA1_HEXSZ)
			die("BUG: oid abbreviation out of range: %d", abbrev);
		if (abbrev)
			hex[abbrev] = '\0';
		return hex;
	}
}

static void fill_metainfo(struct strbuf *msg,
			  const char *name,
