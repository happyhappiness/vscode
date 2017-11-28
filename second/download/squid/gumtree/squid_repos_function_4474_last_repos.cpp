void
free_nd(struct ndstruct *ndsp)
{
    while (ndsp) {
        struct ndstruct *ndspn = ndsp->next;
        xfree(ndsp->netbios);
        xfree(ndsp->domain);
        xfree(ndsp);
        ndsp = ndspn;
    }
}