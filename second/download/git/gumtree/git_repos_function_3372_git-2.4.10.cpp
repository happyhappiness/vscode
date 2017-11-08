static void free_pcre_regexp(struct grep_pat *p)
{
	pcre_free(p->pcre_regexp);
	pcre_free(p->pcre_extra_info);
}