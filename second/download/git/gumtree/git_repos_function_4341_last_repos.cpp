static void free_pcre2_pattern(struct grep_pat *p)
{
	pcre2_compile_context_free(p->pcre2_compile_context);
	pcre2_code_free(p->pcre2_pattern);
	pcre2_match_data_free(p->pcre2_match_data);
	pcre2_jit_stack_free(p->pcre2_jit_stack);
	pcre2_match_context_free(p->pcre2_match_context);
}