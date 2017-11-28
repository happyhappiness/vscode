static void
init_node_hash(struct node *nodes)
{
    register struct node *np, *nextp;
    register char *cp;
    register int hash;

    memset((char *) nbuckets, '\0', sizeof(nbuckets));
    for (np = nodes; np;) {
        nextp = np->next;
        hash = 0;
        for (cp = np->parent; *cp; cp++)
            hash += *cp;
        np->next = nbuckets[NBUCKET(hash)];
        nbuckets[NBUCKET(hash)] = np;
        np = nextp;
    }
}