static NORETURN void compile_regexp_failed(const struct grep_pat *p,
		const char *error)
{
	char where[1024];

	if (p->no)
		xsnprintf(where, sizeof(where), "In '%s' at %d, ", p->origin, p->no);
	else if (p->origin)
		xsnprintf(where, sizeof(where), "%s, ", p->origin);
	else
		where[0] = 0;

	die("%s'%s': %s", where, p->pattern, error);
}