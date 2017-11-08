static void *findMain(void)
{
    struct ld_info *lp;
    char *buf;
    int size = 4 * 1024;
    int i;
    void *ret;

    if ((buf = malloc(size)) == NULL) {
	errvalid++;
	strcpy(errbuf, "findMain: ");
	strcat(errbuf, strerror(errno));
	return NULL;
    }
    while ((i = loadquery(L_GETINFO, buf, size)) == -1 && errno == ENOMEM) {
	free(buf);
	size += 4 * 1024;
	if ((buf = malloc(size)) == NULL) {
	    errvalid++;
	    strcpy(errbuf, "findMain: ");
	    strcat(errbuf, strerror(errno));
	    return NULL;
	}
    }
    if (i == -1) {
	errvalid++;
	strcpy(errbuf, "findMain: ");
	strcat(errbuf, strerror(errno));
	free(buf);
	return NULL;
    }
    /*
     * The first entry is the main module. The data segment
     * starts with the TOC entries for all exports, so the
     * data segment origin works as argument for loadbind.
     */
    lp = (struct ld_info *) buf;
    ret = lp->ldinfo_dataorg;
    free(buf);
    return ret;
}