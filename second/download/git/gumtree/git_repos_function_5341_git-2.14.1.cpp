static const char *get_tag(const struct cache_entry *ce, const char *tag)
{
	static char alttag[4];

	if (tag && *tag && show_valid_bit && (ce->ce_flags & CE_VALID)) {
		memcpy(alttag, tag, 3);

		if (isalpha(tag[0])) {
			alttag[0] = tolower(tag[0]);
		} else if (tag[0] == '?') {
			alttag[0] = '!';
		} else {
			alttag[0] = 'v';
			alttag[1] = tag[0];
			alttag[2] = ' ';
			alttag[3] = 0;
		}

		tag = alttag;
	}

	return tag;
}