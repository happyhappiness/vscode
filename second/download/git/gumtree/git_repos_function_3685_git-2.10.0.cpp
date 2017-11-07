static void grep_set_pattern_type_option(enum grep_pattern_type pattern_type, struct grep_opt *opt)
{
	switch (pattern_type) {
	case GREP_PATTERN_TYPE_UNSPECIFIED:
		/* fall through */

	case GREP_PATTERN_TYPE_BRE:
		opt->fixed = 0;
		opt->pcre = 0;
		opt->regflags &= ~REG_EXTENDED;
		break;

	case GREP_PATTERN_TYPE_ERE:
		opt->fixed = 0;
		opt->pcre = 0;
		opt->regflags |= REG_EXTENDED;
		break;

	case GREP_PATTERN_TYPE_FIXED:
		opt->fixed = 1;
		opt->pcre = 0;
		opt->regflags &= ~REG_EXTENDED;
		break;

	case GREP_PATTERN_TYPE_PCRE:
		opt->fixed = 0;
		opt->pcre = 1;
		opt->regflags &= ~REG_EXTENDED;
		break;
	}
}