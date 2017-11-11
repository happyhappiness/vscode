const char *dlerror(void)
{
    if (errvalid) {
	errvalid = 0;
	return errbuf;
    }
    return NULL;
}