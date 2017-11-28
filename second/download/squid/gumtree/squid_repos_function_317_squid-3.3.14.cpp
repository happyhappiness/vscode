char *
get_netbios_name(struct main_args *margs, char *netbios)
{
    struct ndstruct *nd;

    nd = margs->ndoms;
    while (nd && netbios) {
        debug((char *) "%s| %s: DEBUG: Netbios domain loop: netbios@domain %s@%s\n", LogTime(), PROGRAM, nd->netbios, nd->domain);
        if (nd->netbios && !strcasecmp(nd->netbios, netbios)) {
            debug((char *) "%s| %s: DEBUG: Found netbios@domain %s@%s\n", LogTime(), PROGRAM, nd->netbios, nd->domain);
            return (nd->domain);
        }
        nd = nd->next;
    }

    return NULL;
}