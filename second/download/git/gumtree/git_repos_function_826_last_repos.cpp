const char *get_preferred_languages(void)
{
	const char *retval;

	retval = getenv("LANGUAGE");
	if (retval && *retval)
		return retval;

#ifndef NO_GETTEXT
	retval = setlocale(LC_MESSAGES, NULL);
	if (retval && *retval &&
		strcmp(retval, "C") &&
		strcmp(retval, "POSIX"))
		return retval;
#endif

	return NULL;
}