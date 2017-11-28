void
clean_ls(struct lsstruct *lssp)
{
    struct lsstruct *p = NULL, *pp = NULL;

    p = lssp;
    while (p) {
        while (p->next) {
            pp = p;
            p = p->next;
        }
        safe_free(p->lserver);
        safe_free(p->domain);
        if (pp)
            safe_free(pp->next);
        if (p == lssp)
            safe_free(lssp);
        p = lssp;
    }
}