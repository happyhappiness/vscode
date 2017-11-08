static int parse_pattern_type_arg(const char *opt, const char *arg)
{
	if (!strcmp(arg, "default"))
		return GREP_PATTERN_TYPE_UNSPECIFIED;
	else if (!strcmp(arg, "basic"))
		return GREP_PATTERN_TYPE_BRE;
	else if (!strcmp(arg, "extended"))
		return GREP_PATTERN_TYPE_ERE;
	else if (!strcmp(arg, "fixed"))
		return GREP_PATTERN_TYPE_FIXED;
	else if (!strcmp(arg, "perl"))
		return GREP_PATTERN_TYPE_PCRE;
	die("bad %s argument: %s", opt, arg);
}