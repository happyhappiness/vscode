void
free_gd(struct gdstruct *gdsp)
{
    while (gdsp) {
        struct gdstruct *gdspn = gdsp->next;
        xfree(gdsp->group);
        xfree(gdsp->domain);
        xfree(gdsp);
        gdsp = gdspn;
    }
}