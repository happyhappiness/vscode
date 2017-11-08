int dlclose(void *handle)
{
    register ModulePtr mp = (ModulePtr) handle;
    int result;
    register ModulePtr mp1;

    if (--mp->refCnt > 0)
	return 0;
    if (mp->info && mp->info->fini)
	(*mp->info->fini) ();
    if (mp->cdtors) {
	CdtorPtr cp = mp->cdtors;
	while (cp->init || cp->term) {
	    if (cp->term && cp->init != (void (*)(void)) 0xffffffff)
		(*cp->term) ();
	    cp++;
	}
	/*
	 * If the function to handle global destructors for g++
	 * exists, call it.  --jwe
	 */
    }
    else if (mp->gcc_dtor) {
	(*mp->gcc_dtor) ();
    }
    result = unload(mp->entry);
    if (result == -1) {
	errvalid++;
	strcpy(errbuf, strerror(errno));
    }
    if (mp->exports) {
	register ExportPtr ep;
	register int i;
	for (ep = mp->exports, i = mp->nExports; i; i--, ep++)
	    if (ep->name)
		free(ep->name);
	free(mp->exports);
    }
    if (mp == modList)
	modList = mp->next;
    else {
	for (mp1 = modList; mp1; mp1 = mp1->next)
	    if (mp1->next == mp) {
		mp1->next = mp->next;
		break;
	    }
    }
    free(mp->name);
    free(mp);
    return result;
}