static void do_append_grep_pat(struct grep_pat ***tail, struct grep_pat *p)
{
	**tail = p;
	*tail = &p->next;
	p->next = NULL;

	switch (p->token) {
	case GREP_PATTERN: /* atom */
	case GREP_PATTERN_HEAD:
	case GREP_PATTERN_BODY:
		for (;;) {
			struct grep_pat *new_pat;
			size_t len = 0;
			char *cp = p->pattern + p->patternlen, *nl = NULL;
			while (++len <= p->patternlen) {
				if (*(--cp) == '\n') {
					nl = cp;
					break;
				}
			}
			if (!nl)
				break;
			new_pat = create_grep_pat(nl + 1, len - 1, p->origin,
						  p->no, p->token, p->field);
			new_pat->next = p->next;
			if (!p->next)
				*tail = &new_pat->next;
			p->next = new_pat;
			*nl = '\0';
			p->patternlen -= len;
		}
		break;
	default:
		break;
	}
}