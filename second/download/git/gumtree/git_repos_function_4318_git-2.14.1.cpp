static void free_pcre1_regexp(struct grep_pat *p)
{
	pcre_free(p->pcre1_regexp);
#ifdef GIT_PCRE1_USE_JIT
	if (p->pcre1_jit_on) {
		pcre_free_study(p->pcre1_extra_info);
		pcre_jit_stack_free(p->pcre1_jit_stack);
	} else
#endif
	{
		pcre_free(p->pcre1_extra_info);
	}
	pcre_free((void *)p->pcre1_tables);
}