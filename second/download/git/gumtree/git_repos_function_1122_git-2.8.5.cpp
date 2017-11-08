static void write_accept_language(struct strbuf *buf)
{
	/*
	 * MAX_DECIMAL_PLACES must not be larger than 3. If it is larger than
	 * that, q-value will be smaller than 0.001, the minimum q-value the
	 * HTTP specification allows. See
	 * http://tools.ietf.org/html/rfc7231#section-5.3.1 for q-value.
	 */
	const int MAX_DECIMAL_PLACES = 3;
	const int MAX_LANGUAGE_TAGS = 1000;
	const int MAX_ACCEPT_LANGUAGE_HEADER_SIZE = 4000;
	char **language_tags = NULL;
	int num_langs = 0;
	const char *s = get_preferred_languages();
	int i;
	struct strbuf tag = STRBUF_INIT;

	/* Don't add Accept-Language header if no language is preferred. */
	if (!s)
		return;

	/*
	 * Split the colon-separated string of preferred languages into
	 * language_tags array.
	 */
	do {
		/* collect language tag */
		for (; *s && (isalnum(*s) || *s == '_'); s++)
			strbuf_addch(&tag, *s == '_' ? '-' : *s);

		/* skip .codeset, @modifier and any other unnecessary parts */
		while (*s && *s != ':')
			s++;

		if (tag.len) {
			num_langs++;
			REALLOC_ARRAY(language_tags, num_langs);
			language_tags[num_langs - 1] = strbuf_detach(&tag, NULL);
			if (num_langs >= MAX_LANGUAGE_TAGS - 1) /* -1 for '*' */
				break;
		}
	} while (*s++);

	/* write Accept-Language header into buf */
	if (num_langs) {
		int last_buf_len = 0;
		int max_q;
		int decimal_places;
		char q_format[32];

		/* add '*' */
		REALLOC_ARRAY(language_tags, num_langs + 1);
		language_tags[num_langs++] = "*"; /* it's OK; this won't be freed */

		/* compute decimal_places */
		for (max_q = 1, decimal_places = 0;
		     max_q < num_langs && decimal_places <= MAX_DECIMAL_PLACES;
		     decimal_places++, max_q *= 10)
			;

		xsnprintf(q_format, sizeof(q_format), ";q=0.%%0%dd", decimal_places);

		strbuf_addstr(buf, "Accept-Language: ");

		for (i = 0; i < num_langs; i++) {
			if (i > 0)
				strbuf_addstr(buf, ", ");

			strbuf_addstr(buf, language_tags[i]);

			if (i > 0)
				strbuf_addf(buf, q_format, max_q - i);

			if (buf->len > MAX_ACCEPT_LANGUAGE_HEADER_SIZE) {
				strbuf_remove(buf, last_buf_len, buf->len - last_buf_len);
				break;
			}

			last_buf_len = buf->len;
		}
	}

	/* free language tags -- last one is a static '*' */
	for (i = 0; i < num_langs - 1; i++)
		free(language_tags[i]);
	free(language_tags);
}