struct lsstruct *
init_ls(void) {
    struct lsstruct *lssp;
    lssp = (struct lsstruct *) xmalloc(sizeof(struct lsstruct));
    lssp->lserver = NULL;
    lssp->domain = NULL;
    lssp->next = NULL;
    return lssp;
}