static int fsck_ident(const char **ident, struct object *obj, fsck_error error_func)
{
	char *end;

	if (**ident == '<')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - missing space before email");
	*ident += strcspn(*ident, "<>\n");
	if (**ident == '>')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - bad name");
	if (**ident != '<')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - missing email");
	if ((*ident)[-1] != ' ')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - missing space before email");
	(*ident)++;
	*ident += strcspn(*ident, "<>\n");
	if (**ident != '>')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - bad email");
	(*ident)++;
	if (**ident != ' ')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - missing space before date");
	(*ident)++;
	if (**ident == '0' && (*ident)[1] != ' ')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - zero-padded date");
	if (date_overflows(strtoul(*ident, &end, 10)))
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - date causes integer overflow");
	if (end == *ident || *end != ' ')
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - bad date");
	*ident = end + 1;
	if ((**ident != '+' && **ident != '-') ||
	    !isdigit((*ident)[1]) ||
	    !isdigit((*ident)[2]) ||
	    !isdigit((*ident)[3]) ||
	    !isdigit((*ident)[4]) ||
	    ((*ident)[5] != '\n'))
		return error_func(obj, FSCK_ERROR, "invalid author/committer line - bad time zone");
	(*ident) += 6;
	return 0;
}