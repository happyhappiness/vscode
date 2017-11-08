static int readExports(ModulePtr mp)
{
    LDFILE *ldp = NULL;
    SCNHDR sh, shdata;
    LDHDR *lhp;
    char *ldbuf;
    LDSYM *ls;
    int i;
    ExportPtr ep;
    struct ld_info *lp;
    char *buf;
    int size = 4 * 1024;
    void *dataorg;

    /*
     * The module might be loaded due to the LIBPATH
     * environment variable. Search for the loaded
     * module using L_GETINFO.
     */
    if ((buf = malloc(size)) == NULL) {
	errvalid++;
	strcpy(errbuf, "readExports: ");
	strcat(errbuf, strerror(errno));
	return -1;
    }
    while ((i = loadquery(L_GETINFO, buf, size)) == -1 && errno == ENOMEM) {
	free(buf);
	size += 4 * 1024;
	if ((buf = malloc(size)) == NULL) {
	    errvalid++;
	    strcpy(errbuf, "readExports: ");
	    strcat(errbuf, strerror(errno));
	    return -1;
	}
    }
    if (i == -1) {
	errvalid++;
	strcpy(errbuf, "readExports: ");
	strcat(errbuf, strerror(errno));
	free(buf);
	return -1;
    }
    /*
     * Traverse the list of loaded modules. The entry point
     * returned by load() does actually point to the TOC
     * entry contained in the data segment.
     */
    lp = (struct ld_info *) buf;
    while (lp) {
	if ((unsigned long) mp->entry >= (unsigned long) lp->ldinfo_dataorg &&
	    (unsigned long) mp->entry < (unsigned long) lp->ldinfo_dataorg +
	    lp->ldinfo_datasize) {
	    dataorg = lp->ldinfo_dataorg;
	    ldp = ldopen(lp->ldinfo_filename, ldp);
	    break;
	}
	if (lp->ldinfo_next == 0)
	    lp = NULL;
	else
	    lp = (struct ld_info *) ((char *) lp + lp->ldinfo_next);
    }
    free(buf);
    if (!ldp) {
	errvalid++;
	strcpy(errbuf, "readExports: ");
	strcat(errbuf, strerror(errno));
	return -1;
    }
    if (TYPE(ldp) != U802TOCMAGIC) {
	errvalid++;
	strcpy(errbuf, "readExports: bad magic");
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    /*
     * Get the padding for the data section. This is needed for
     * AIX 4.1 compilers. This is used when building the final
     * function pointer to the exported symbol.
     */
    if (ldnshread(ldp, _DATA, &shdata) != SUCCESS) {
	errvalid++;
	strcpy(errbuf, "readExports: cannot read data section header");
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    if (ldnshread(ldp, _LOADER, &sh) != SUCCESS) {
	errvalid++;
	strcpy(errbuf, "readExports: cannot read loader section header");
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    /*
     * We read the complete loader section in one chunk, this makes
     * finding long symbol names residing in the string table easier.
     */
    if ((ldbuf = (char *) malloc(sh.s_size)) == NULL) {
	errvalid++;
	strcpy(errbuf, "readExports: ");
	strcat(errbuf, strerror(errno));
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    if (FSEEK(ldp, sh.s_scnptr, BEGINNING) != OKFSEEK) {
	errvalid++;
	strcpy(errbuf, "readExports: cannot seek to loader section");
	free(ldbuf);
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    if (FREAD(ldbuf, sh.s_size, 1, ldp) != 1) {
	errvalid++;
	strcpy(errbuf, "readExports: cannot read loader section");
	free(ldbuf);
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    lhp = (LDHDR *) ldbuf;
    ls = (LDSYM *) (ldbuf + LDHDRSZ);
    /*
     * Count the number of exports to include in our export table.
     */
    for (i = lhp->l_nsyms; i; i--, ls++) {
	if (!LDR_EXPORT(*ls))
	    continue;
	mp->nExports++;
    }
    if ((mp->exports = (ExportPtr) calloc(mp->nExports, sizeof(*mp->exports))) == NULL) {
	errvalid++;
	strcpy(errbuf, "readExports: ");
	strcat(errbuf, strerror(errno));
	free(ldbuf);
	while (ldclose(ldp) == FAILURE);
	return -1;
    }
    /*
     * Fill in the export table. All entries are relative to
     * the beginning of the data origin.
     */
    ep = mp->exports;
    ls = (LDSYM *) (ldbuf + LDHDRSZ);
    for (i = lhp->l_nsyms; i; i--, ls++) {
	char *symname;
	char tmpsym[SYMNMLEN + 1];
	if (!LDR_EXPORT(*ls))
	    continue;
	if (ls->l_zeroes == 0)
	    symname = ls->l_offset + lhp->l_stoff + ldbuf;
	else {
	    /*
	     * The l_name member is not zero terminated, we
	     * must copy the first SYMNMLEN chars and make
	     * sure we have a zero byte at the end.
	     */
	    strncpy(tmpsym, ls->l_name, SYMNMLEN);
	    tmpsym[SYMNMLEN] = '\0';
	    symname = tmpsym;
	}
	ep->name = strdup(symname);
	ep->addr = (void *) ((unsigned long) dataorg +
			     ls->l_value - shdata.s_vaddr);
	ep++;
    }
    free(ldbuf);
    while (ldclose(ldp) == FAILURE);
    return 0;
}