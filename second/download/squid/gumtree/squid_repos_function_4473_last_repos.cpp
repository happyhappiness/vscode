struct ndstruct *
init_nd(void) {
    struct ndstruct *ndsp;
    ndsp = (struct ndstruct *) xmalloc(sizeof(struct ndstruct));
    ndsp->netbios = NULL;
    ndsp->domain = NULL;
    ndsp->next = NULL;
    return ndsp;
}