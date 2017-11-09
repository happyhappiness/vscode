static char *canon_name_from_hostent(struct hostent *hp,
				int *perr)
{
	char *ret = NULL;

	*perr = check_hostent_err(hp);
	if (*perr) {
		return NULL;
	}
	ret = SMB_STRDUP(hp->h_name);
	if (!ret) {
		*perr = EAI_MEMORY;
	}
	return ret;
}