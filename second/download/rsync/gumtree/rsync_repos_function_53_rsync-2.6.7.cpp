char *get_rule_prefix(int match_flags, const char *pat, int for_xfer,
		      unsigned int *plen_ptr)
{
	static char buf[MAX_RULE_PREFIX+1];
	char *op = buf;
	int legal_len = for_xfer && protocol_version < 29 ? 1 : MAX_RULE_PREFIX-1;

	if (match_flags & MATCHFLG_PERDIR_MERGE) {
		if (legal_len == 1)
			return NULL;
		*op++ = ':';
	} else if (match_flags & MATCHFLG_INCLUDE)
		*op++ = '+';
	else if (legal_len != 1
	    || ((*pat == '-' || *pat == '+') && pat[1] == ' '))
		*op++ = '-';
	else
		legal_len = 0;

	if (match_flags & MATCHFLG_CVS_IGNORE)
		*op++ = 'C';
	else {
		if (match_flags & MATCHFLG_NO_INHERIT)
			*op++ = 'n';
		if (match_flags & MATCHFLG_WORD_SPLIT)
			*op++ = 'w';
		if (match_flags & MATCHFLG_NO_PREFIXES) {
			if (match_flags & MATCHFLG_INCLUDE)
				*op++ = '+';
			else
				*op++ = '-';
		}
	}
	if (match_flags & MATCHFLG_EXCLUDE_SELF)
		*op++ = 'e';
	if (match_flags & MATCHFLG_SENDER_SIDE
	    && (!for_xfer || protocol_version >= 29))
		*op++ = 's';
	if (match_flags & MATCHFLG_RECEIVER_SIDE
	    && (!for_xfer || protocol_version >= 29
	     || (delete_excluded && am_sender)))
		*op++ = 'r';
	if (op - buf > legal_len)
		return NULL;
	if (legal_len)
		*op++ = ' ';
	*op = '\0';
	if (plen_ptr)
		*plen_ptr = op - buf;
	return buf;
}