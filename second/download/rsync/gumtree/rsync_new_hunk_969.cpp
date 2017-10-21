		return str + rule_len - 1;
	if (str[rule_len] == ',')
		return str + rule_len;
	return NULL;
}

#define FILTRULES_FROM_CONTAINER (FILTRULE_ABS_PATH | FILTRULE_INCLUDE \
				| FILTRULE_DIRECTORY | FILTRULE_NEGATE \
				| FILTRULE_PERISHABLE)

/* Gets the next include/exclude rule from *rulestr_ptr and advances
 * *rulestr_ptr to point beyond it.  Stores the pattern's start (within
 * *rulestr_ptr) and length in *pat_ptr and *pat_len_ptr, and returns a newly
 * allocated filter_rule containing the rest of the information.  Returns
 * NULL if there are no more rules in the input.
 *
 * The template provides defaults for the new rule to inherit, and the
 * template rflags and the xflags additionally affect parsing. */
static filter_rule *parse_rule_tok(const char **rulestr_ptr,
				   const filter_rule *template, int xflags,
				   const char **pat_ptr, unsigned int *pat_len_ptr)
{
	const uchar *s = (const uchar *)*rulestr_ptr;
	filter_rule *rule;
	unsigned int len;

	if (template->rflags & FILTRULE_WORD_SPLIT) {
		/* Skip over any initial whitespace. */
		while (isspace(*s))
			s++;
		/* Update to point to real start of rule. */
		*rulestr_ptr = (const char *)s;
	}
	if (!*s)
		return NULL;

	if (!(rule = new0(filter_rule)))
		out_of_memory("parse_rule_tok");

	/* Inherit from the template.  Don't inherit FILTRULES_SIDES; we check
	 * that later. */
	rule->rflags = template->rflags & FILTRULES_FROM_CONTAINER;

	/* Figure out what kind of a filter rule "s" is pointing at.  Note
	 * that if FILTRULE_NO_PREFIXES is set, the rule is either an include
	 * or an exclude based on the inheritance of the FILTRULE_INCLUDE
	 * flag (above).  XFLG_OLD_PREFIXES indicates a compatibility mode
	 * for old include/exclude patterns where just "+ " and "- " are
	 * allowed as optional prefixes.  */
	if (template->rflags & FILTRULE_NO_PREFIXES) {
		if (*s == '!' && template->rflags & FILTRULE_CVS_IGNORE)
			rule->rflags |= FILTRULE_CLEAR_LIST; /* Tentative! */
	} else if (xflags & XFLG_OLD_PREFIXES) {
		if (*s == '-' && s[1] == ' ') {
			rule->rflags &= ~FILTRULE_INCLUDE;
			s += 2;
		} else if (*s == '+' && s[1] == ' ') {
			rule->rflags |= FILTRULE_INCLUDE;
			s += 2;
		} else if (*s == '!')
			rule->rflags |= FILTRULE_CLEAR_LIST; /* Tentative! */
	} else {
		char ch = 0;
		BOOL prefix_specifies_side = False;
		switch (*s) {
		case 'c':
			if ((s = RULE_STRCMP(s, "clear")) != NULL)
				ch = '!';
			break;
		case 'd':
