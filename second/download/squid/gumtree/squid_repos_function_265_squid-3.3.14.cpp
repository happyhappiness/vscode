void
clean_nd(struct ndstruct *ndsp)
{
    struct ndstruct *p = NULL, *pp = NULL;

    p = ndsp;
    while (p) {
        while (p->next) {
            pp = p;
            p = p->next;
        }
        if (p->netbios) {
            xfree(p->netbios);
            p->netbios = NULL;
        }
        if (p->domain) {
            xfree(p->domain);
            p->domain = NULL;
        }
        if (pp && pp->next) {
            xfree(pp->next);
            pp->next = NULL;
        }
        if (p == ndsp) {
            xfree(ndsp);
            ndsp = NULL;
        }
        p = ndsp;
    }
}