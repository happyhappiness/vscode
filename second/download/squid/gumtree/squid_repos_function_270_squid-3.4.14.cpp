struct gdstruct *
init_gd(void) {
    struct gdstruct *gdsp;
    gdsp = (struct gdstruct *) xmalloc(sizeof(struct gdstruct));
    gdsp->group = NULL;
    gdsp->domain = NULL;
    gdsp->next = NULL;
    return gdsp;
}