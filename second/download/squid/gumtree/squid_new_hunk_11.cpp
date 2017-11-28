        free_node(np);
        return 0;
    }
    length = getoid(fp, SubOid, 32);
    if (length > 1 && length <= 32) {
        /* just take the last pair in the oid list */
        if (SubOid[length - 2].label) {
            strncpy(np->parent, SubOid[length - 2].label, 64);
            np->parent[63] = '\0';
        }
        strncpy(np->label, name, sizeof(np->label));
        np->label[sizeof(np->label) - 1] = '\0';
        if (SubOid[length - 1].subid != -1)
            np->subid = SubOid[length - 1].subid;
        else
            print_error("Warning: This entry is pretty silly", np->label, type);
    } else {
        print_error("No end to oid", (char *) NULL, type);
