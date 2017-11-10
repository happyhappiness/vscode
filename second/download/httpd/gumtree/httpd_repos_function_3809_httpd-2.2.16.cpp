void *dlopen(const char *path, int mode)
{
    register ModulePtr mp;
    static void *mainModule;

    /*
     * Upon the first call register a terminate handler that will
     * close all libraries. Also get a reference to the main module
     * for use with loadbind.
     */
    if (!mainModule) {
	if ((mainModule = findMain()) == NULL)
	    return NULL;
	atexit(terminate);
    }
    /*
     * Scan the list of modules if we have the module already loaded.
     */
    for (mp = modList; mp; mp = mp->next)
	if (strcmp(mp->name, path) == 0) {
	    mp->refCnt++;
	    return mp;
	}
    if ((mp = (ModulePtr) calloc(1, sizeof(*mp))) == NULL) {
	errvalid++;
	strcpy(errbuf, "calloc: ");
	strcat(errbuf, strerror(errno));
	return NULL;
    }
    if ((mp->name = strdup(path)) == NULL) {
	errvalid++;
	strcpy(errbuf, "strdup: ");
	strcat(errbuf, strerror(errno));
	free(mp);
	return NULL;
    }
    /*
     * load should be declared load(const char *...). Thus we
     * cast the path to a normal char *. Ugly.
     */
    if ((mp->entry = (void *) loadAndInit((char *) path, L_NOAUTODEFER, NULL)) == NULL) {
	free(mp->name);
	free(mp);
	errvalid++;
	strcpy(errbuf, "dlopen: ");
	strcat(errbuf, path);
	strcat(errbuf, ": ");
	/*
	 * If AIX says the file is not executable, the error
	 * can be further described by querying the loader about
	 * the last error.
	 */
	if (errno == ENOEXEC) {
	    char *tmp[BUFSIZ / sizeof(char *)];
	    if (loadquery(L_GETMESSAGES, tmp, sizeof(tmp)) == -1)
		strcpy(errbuf, strerror(errno));
	    else {
		char **p;
		for (p = tmp; *p; p++)
		    caterr(*p);
	    }
	}
	else
	    strcat(errbuf, strerror(errno));
	return NULL;
    }
    mp->refCnt = 1;
    mp->next = modList;
    modList = mp;
    if (loadbind(0, mainModule, mp->entry) == -1) {
	dlclose(mp);
	errvalid++;
	strcpy(errbuf, "loadbind: ");
	strcat(errbuf, strerror(errno));
	return NULL;
    }
    /*
     * If the user wants global binding, loadbind against all other
     * loaded modules.
     */
    if (mode & RTLD_GLOBAL) {
	register ModulePtr mp1;
	for (mp1 = mp->next; mp1; mp1 = mp1->next)
	    if (loadbind(0, mp1->entry, mp->entry) == -1) {
		dlclose(mp);
		errvalid++;
		strcpy(errbuf, "loadbind: ");
		strcat(errbuf, strerror(errno));
		return NULL;
	    }
    }
    if (readExports(mp) == -1) {
	dlclose(mp);
	return NULL;
    }
    /*
     * If there is a dl_info structure, call the init function.
     */
    if (mp->info = (struct dl_info *) dlsym(mp, "dl_info")) {
	if (mp->info->init)
	    (*mp->info->init) ();
    }
    else
	errvalid = 0;
    /*
     * If the shared object was compiled using xlC we will need
     * to call static constructors (and later on dlclose destructors).
     */
    if (mp->cdtors = (CdtorPtr) dlsym(mp, "__cdtors")) {
	CdtorPtr cp = mp->cdtors;
	while (cp->init || cp->term) {
	    if (cp->init && cp->init != (void (*)(void)) 0xffffffff)
		(*cp->init) ();
	    cp++;
	}
	/*
	 * If the shared object was compiled using g++, we will need
	 * to call global constructors using the _GLOBAL__DI function,
	 * and later, global destructors using the _GLOBAL_DD
	 * funciton.  --jwe
	 */
    }
    else if (mp->gcc_ctor = (GccCDtorPtr) dlsym(mp, "_GLOBAL__DI")) {
	(*mp->gcc_ctor) ();
	mp->gcc_dtor = (GccCDtorPtr) dlsym(mp, "_GLOBAL__DD");
    }
    else
	errvalid = 0;
    return mp;
}