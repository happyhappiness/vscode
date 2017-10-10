}

static void free_pcre_regexp(struct grep_pat *p)
{
	pcre_free(p->pcre_regexp);
	pcre_free(p->pcre_extra_info);
	pcre_free((void *)p->pcre_tables);
}
#else /* !USE_LIBPCRE */
static void compile_pcre_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}
