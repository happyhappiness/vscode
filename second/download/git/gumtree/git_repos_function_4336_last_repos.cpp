static void compile_pcre1_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}