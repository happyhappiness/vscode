static char *parse_name_and_email(char *buffer, char **name,
				  char **email, int allow_empty_email)
{
	char *left, *right, *nstart, *nend;
	*name = *email = NULL;

	if ((left = strchr(buffer, '<')) == NULL)
		return NULL;
	if ((right = strchr(left+1, '>')) == NULL)
		return NULL;
	if (!allow_empty_email && (left+1 == right))
		return NULL;

	/* remove whitespace from beginning and end of name */
	nstart = buffer;
	while (isspace(*nstart) && nstart < left)
		++nstart;
	nend = left-1;
	while (nend > nstart && isspace(*nend))
		--nend;

	*name = (nstart <= nend ? nstart : NULL);
	*email = left+1;
	*(nend+1) = '\0';
	*right++ = '\0';

	return (*right == '\0' ? NULL : right);
}