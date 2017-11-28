static void
do_subtree(struct snmp_mib_tree *root, struct node **nodes)
{
    register struct snmp_mib_tree *tp;
    struct snmp_mib_tree *peer = NULL;
    register struct node *np = NULL, **headp = NULL;
    struct node *oldnp = NULL, *child_list = NULL, *childp = NULL;
    char *cp;
    int hash;

    tp = root;
    hash = 0;
    for (cp = tp->label; *cp; cp++)
        hash += *cp;
    headp = &nbuckets[NBUCKET(hash)];
    /*
     * Search each of the nodes for one whose parent is root, and
     * move each into a separate list.
     */
    for (np = *headp; np; np = np->next) {
        if ((*tp->label != *np->parent) || strcmp(tp->label, np->parent)) {
            if ((*tp->label == *np->label) && !strcmp(tp->label, np->label)) {
                /* if there is another node with the same label, assume that
                 * any children after this point in the list belong to the other node.
                 * This adds some scoping to the table and allows vendors to
                 * reuse names such as "ip".
                 */
                break;
            }
            oldnp = np;
        } else {
            if (child_list == NULL) {
                child_list = childp = np;	/* first entry in child list */
            } else {
                childp->next = np;
                childp = np;
            }
            /* take this node out of the node list */
            if (oldnp == NULL) {
                *headp = np->next;	/* fix root of node list */
            } else {
                oldnp->next = np->next;		/* link around this node */
            }
        }
    }
    if (childp)
        childp->next = 0;	/* re-terminate list */
    /*
     * Take each element in the child list and place it into the tree.
     */
    for (np = child_list; np; np = np->next) {
        tp = (struct snmp_mib_tree *) xmalloc(sizeof(struct snmp_mib_tree));
        tp->parent = root;
        tp->next_peer = NULL;
        tp->child_list = NULL;
        strcpy(tp->label, np->label);
        tp->subid = np->subid;
        tp->type = translation_table[np->type];
        tp->enums = np->enums;
        np->enums = NULL;	/* so we don't free them later */
        if (root->child_list == NULL) {
            root->child_list = tp;
        } else if (peer) {
            peer->next_peer = tp;
        }
        peer = tp;
        /*      if (tp->type == TYPE_OTHER) */
        do_subtree(tp, nodes);	/* recurse on this child if it isn't an end node */
    }
    /* free all nodes that were copied into tree */
    oldnp = NULL;
    for (np = child_list; np; np = np->next) {
        if (oldnp)
            xfree(oldnp);
        oldnp = np;
    }
    if (oldnp)
        xfree(oldnp);
}