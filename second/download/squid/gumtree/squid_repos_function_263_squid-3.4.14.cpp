void
clean_gd(struct gdstruct *gdsp)
{
    struct gdstruct *p = NULL, *pp = NULL;

    p = gdsp;
    while (p) {
        while (p->next) {
            pp = p;
            p = p->next;
        }
        safe_free(p->group);
        safe_free(p->domain);
        if (pp)
            safe_free(pp->next);
        if (p == gdsp)
            safe_free(gdsp);
        p = gdsp;
    }
}