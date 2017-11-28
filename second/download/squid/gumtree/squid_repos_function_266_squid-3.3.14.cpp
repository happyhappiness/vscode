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
        if (p->lserver) {
            xfree(p->lserver);
            p->lserver = NULL;
        }
        if (p->domain) {
            xfree(p->domain);
            p->domain = NULL;
        }
        if (pp && pp->next) {
            xfree(pp->next);
            pp->next = NULL;
        }
        if (p == lssp) {
            xfree(lssp);
            lssp = NULL;
        }
        p = lssp;
    }
}