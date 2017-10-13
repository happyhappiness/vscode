static void compile_pcre2_pattern(struct grep_pat *p, const struct grep_opt *opt)
{
	/*
	 * Unreachable until USE_LIBPCRE2 becomes synonymous with
	 * USE_LIBPCRE. See the sibling comment in
	 * grep_set_pattern_type_option().
	 */
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}