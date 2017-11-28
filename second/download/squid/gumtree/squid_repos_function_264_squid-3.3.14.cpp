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
        if (p->group) {
            xfree(p->group);
            p->group = NULL;
        }
        if (p->domain) {
            xfree(p->domain);
            p->domain = NULL;
        }
        if (pp && pp->next) {
            xfree(pp->next);
            pp->next = NULL;
        }
        if (p == gdsp) {
            xfree(gdsp);
            gdsp = NULL;
        }
        p = gdsp;
    }
}