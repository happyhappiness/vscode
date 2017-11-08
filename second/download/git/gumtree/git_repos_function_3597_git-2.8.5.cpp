void grep_commit_pattern_type(enum grep_pattern_type pattern_type, struct grep_opt *opt)
{
	if (pattern_type != GREP_PATTERN_TYPE_UNSPECIFIED)
		grep_set_pattern_type_option(pattern_type, opt);
	else if (opt->pattern_type_option != GREP_PATTERN_TYPE_UNSPECIFIED)
		grep_set_pattern_type_option(opt->pattern_type_option, opt);
	else if (opt->extended_regexp_option)
		grep_set_pattern_type_option(GREP_PATTERN_TYPE_ERE, opt);
}