         * care of here.  The name for this node is taken from the label for this
         * entry.
         * np still points to an unused entry.
         */
        if (count == (length - 2)) {
            if (op->label) {
                strncpy(np->parent, op->label, sizeof(np->parent));
                strncpy(np->label, name, sizeof(np->label));
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
