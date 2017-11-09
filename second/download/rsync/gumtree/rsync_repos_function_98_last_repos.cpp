char *get_rule_prefix(filter_rule *rule, const char *pat, int for_xfer,
		      unsigned int *plen_ptr)
{
	static char buf[MAX_RULE_PREFIX+1];
	char *op = buf;
	int legal_len = for_xfer && protocol_version < 29 ? 1 : MAX_RULE_PREFIX-1;

	if (rule->rflags & FILTRULE_PERDIR_MERGE) {
		if (legal_len == 1)
			return NULL;
		*op++ = ':';
	} else if (rule->rflags & FILTRULE_INCLUDE)
		*op++ = '+';
	else if (legal_len != 1
	    || ((*pat == '-' || *pat == '+') && pat[1] == ' '))
		*op++ = '-';
	else
		legal_len = 0;

	if (rule->rflags & FILTRULE_ABS_PATH)
		*op++ = '/';
	if (rule->rflags & FILTRULE_NEGATE)
		*op++ = '!';
	if (rule->rflags & FILTRULE_CVS_IGNORE)
		*op++ = 'C';
	else {
		if (rule->rflags & FILTRULE_NO_INHERIT)
			*op++ = 'n';
		if (rule->rflags & FILTRULE_WORD_SPLIT)
			*op++ = 'w';
		if (rule->rflags & FILTRULE_NO_PREFIXES) {
			if (rule->rflags & FILTRULE_INCLUDE)
				*op++ = '+';
			else
				*op++ = '-';
		}
	}
	if (rule->rflags & FILTRULE_EXCLUDE_SELF)
		*op++ = 'e';
	if (rule->rflags & FILTRULE_SENDER_SIDE
	    && (!for_xfer || protocol_version >= 29))
		*op++ = 's';
	if (rule->rflags & FILTRULE_RECEIVER_SIDE
	    && (!for_xfer || protocol_version >= 29
	     || (delete_excluded && am_sender)))
		*op++ = 'r';
	if (rule->rflags & FILTRULE_PERISHABLE) {
		if (!for_xfer || protocol_version >= 30)
			*op++ = 'p';
		else if (am_sender)
			return NULL;
	}
	if (op - buf > legal_len)
		return NULL;
	if (legal_len)
		*op++ = ' ';
	*op = '\0';
	if (plen_ptr)
		*plen_ptr = op - buf;
	return buf;
}