static char *get_my_canon_name(int *perr)
{
	char name[HOST_NAME_MAX+1];

	if (gethostname(name, HOST_NAME_MAX) == -1) {
		*perr = EAI_FAIL;
		return NULL;
	}
	/* Ensure null termination. */
	name[HOST_NAME_MAX] = '\0';
	return canon_name_from_hostent(gethostbyname(name), perr);
}