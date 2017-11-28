static struct node *
parse_objectid(FILE *fp, char *name) {
    int type;
    char token[64];
    register int count;
    register struct subid *op, *nop;
    int length;
    struct subid SubOid[32];
    struct node *np, *root, *oldnp = NULL;

    type = get_token(fp, token);
    if (type != EQUALS) {
        print_error("Bad format", token, type);
        return 0;
    }
    if ((length = getoid(fp, SubOid, 32)) != 0) {
        np = root = (struct node *) xmalloc(sizeof(struct node));
        memset((char *) np, '\0', sizeof(struct node));
        /*
         * For each parent-child subid pair in the subid array,
         * create a node and link it into the node list.
         */
        for (count = 0, op = SubOid, nop = SubOid + 1; count < (length - 2); count++,
                op++, nop++) {
            /* every node must have parent's name and child's name or number */
            if (op->label && (nop->label || (nop->subid != -1))) {
                strncpy(np->parent, op->label, sizeof(np->parent) - 1);
                if (nop->label)
                    strncpy(np->label, nop->label, sizeof(np->label) - 1);
                if (nop->subid != -1)
                    np->subid = nop->subid;
                np->type = 0;
                np->enums = 0;
                /* set up next entry */
                np->next = (struct node *) xmalloc(sizeof(*np->next));
                memset((char *) np->next, '\0', sizeof(struct node));
                oldnp = np;
                np = np->next;
            }
        }
        np->next = (struct node *) NULL;
        /*
         * The above loop took care of all but the last pair.  This pair is taken
         * care of here.  The name for this node is taken from the label for this
         * entry.
         * np still points to an unused entry.
         */
        if (count == (length - 2)) {
            if (op->label) {
                strncpy(np->parent, op->label, sizeof(np->parent));
                np->parent[sizeof(np->parent-1)] = '\0';
                strncpy(np->label, name, sizeof(np->label));
                np->label[sizeof(np->label-1)] = '\0';
                if (nop->subid != -1)
                    np->subid = nop->subid;
                else
                    print_error("Warning: This entry is pretty silly", np->label, type);
            } else {
                free_node(np);
                if (oldnp)
                    oldnp->next = NULL;
                else {
                    free_node_list(root); // we need to clear the newly allocated list
                    return NULL;
                }
            }
        } else {
            print_error("Missing end of oid", (char *) NULL, type);
            free_node_list(root); // we need to clear the newly allocated list
            if (oldnp)
                oldnp->next = NULL;
            return NULL;
        }
        /* free the oid array */
        for (count = 0, op = SubOid; count < length; count++, op++) {
            if (op->label)
                xfree(op->label);
            op->label = 0;
        }
        return root;
    } else {
        print_error("Bad object identifier", (char *) NULL, type);
        return 0;
    }
}