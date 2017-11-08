void free_grep_patterns(struct grep_opt *opt)
{
	struct grep_pat *p, *n;

	for (p = opt->pattern_list; p; p = n) {
		n = p->next;
		switch (p->token) {
		case GREP_PATTERN: /* atom */
		case GREP_PATTERN_HEAD:
		case GREP_PATTERN_BODY:
			if (p->kws)
				kwsfree(p->kws);
			else if (p->pcre1_regexp)
				free_pcre1_regexp(p);
			else if (p->pcre2_pattern)
				free_pcre2_pattern(p);
			else
				regfree(&p->regexp);
			free(p->pattern);
			break;
		default:
			break;
		}
		free(p);
	}

	if (!opt->extended)
		return;
	free_pattern_expr(opt->pattern_expression);
}