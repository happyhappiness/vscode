static int ident_filter_fn(struct stream_filter *filter,
			   const char *input, size_t *isize_p,
			   char *output, size_t *osize_p)
{
	struct ident_filter *ident = (struct ident_filter *)filter;
	static const char head[] = "$Id";

	if (!input) {
		/* drain upon eof */
		switch (ident->state) {
		default:
			strbuf_add(&ident->left, head, ident->state);
		case IDENT_SKIPPING:
			/* fallthru */
		case IDENT_DRAINING:
			ident_drain(ident, &output, osize_p);
		}
		return 0;
	}

	while (*isize_p || (ident->state == IDENT_DRAINING)) {
		int ch;

		if (ident->state == IDENT_DRAINING) {
			ident_drain(ident, &output, osize_p);
			if (!*osize_p)
				break;
			continue;
		}

		ch = *(input++);
		(*isize_p)--;

		if (ident->state == IDENT_SKIPPING) {
			/*
			 * Skipping until '$' or LF, but keeping them
			 * in case it is a foreign ident.
			 */
			strbuf_addch(&ident->left, ch);
			if (ch != '\n' && ch != '$')
				continue;
			if (ch == '$' && !is_foreign_ident(ident->left.buf)) {
				strbuf_setlen(&ident->left, sizeof(head) - 1);
				strbuf_addstr(&ident->left, ident->ident);
			}
			ident->state = IDENT_DRAINING;
			continue;
		}

		if (ident->state < sizeof(head) &&
		    head[ident->state] == ch) {
			ident->state++;
			continue;
		}

		if (ident->state)
			strbuf_add(&ident->left, head, ident->state);
		if (ident->state == sizeof(head) - 1) {
			if (ch != ':' && ch != '$') {
				strbuf_addch(&ident->left, ch);
				ident->state = 0;
				continue;
			}

			if (ch == ':') {
				strbuf_addch(&ident->left, ch);
				ident->state = IDENT_SKIPPING;
			} else {
				strbuf_addstr(&ident->left, ident->ident);
				ident->state = IDENT_DRAINING;
			}
			continue;
		}

		strbuf_addch(&ident->left, ch);
		ident->state = IDENT_DRAINING;
	}
	return 0;
}