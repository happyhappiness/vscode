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
        safe_free(p->netbios);
        safe_free(p->domain);
        if (pp)
            safe_free(pp->next);
        if (p == ndsp)
            safe_free(ndsp);
        p = ndsp;
    }
}