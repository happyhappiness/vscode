static int parse_decorate_color_slot(const char *slot)
{
	/*
	 * We're comparing with 'ignore-case' on
	 * (because config.c sets them all tolower),
	 * but let's match the letters in the literal
	 * string values here with how they are
	 * documented in Documentation/config.txt, for
	 * consistency.
	 *
	 * We love being consistent, don't we?
	 */
	if (!strcasecmp(slot, "branch"))
		return DECORATION_REF_LOCAL;
	if (!strcasecmp(slot, "remoteBranch"))
		return DECORATION_REF_REMOTE;
	if (!strcasecmp(slot, "tag"))
		return DECORATION_REF_TAG;
	if (!strcasecmp(slot, "stash"))
		return DECORATION_REF_STASH;
	if (!strcasecmp(slot, "HEAD"))
		return DECORATION_REF_HEAD;
	return -1;
}