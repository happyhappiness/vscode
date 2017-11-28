void
free_ls(struct lsstruct *lssp)
{
    while (lssp) {
        struct lsstruct *lsspn = lssp->next;
        xfree(lssp->lserver);
        xfree(lssp->domain);
        xfree(lssp);
        lssp = lsspn;
    }
}