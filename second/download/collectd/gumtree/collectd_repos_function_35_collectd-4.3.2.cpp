static const char *
lt_int_dyld_error(othererror)
	char* othererror;
{
/* return the dyld error string, or the passed in error string if none */
	NSLinkEditErrors ler;
	int lerno;
	const char *errstr;
	const char *file;
	NSLinkEditError(&ler,&lerno,&file,&errstr);
	if (!errstr || !strlen(errstr)) errstr = othererror;
	return errstr;
}