void *dlsym(void *handle, const char *symbol)
{
    register ModulePtr mp = (ModulePtr) handle;
    register ExportPtr ep;
    register int i;

    /*
     * Could speed up the search, but I assume that one assigns
     * the result to function pointers anyways.
     */
    for (ep = mp->exports, i = mp->nExports; i; i--, ep++)
	if (strcmp(ep->name, symbol) == 0)
	    return ep->addr;
    errvalid++;
    strcpy(errbuf, "dlsym: undefined symbol ");
    strcat(errbuf, symbol);
    return NULL;
}