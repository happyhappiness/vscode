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
