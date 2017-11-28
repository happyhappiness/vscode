    AclMatchedName = NULL;	/* ugly */

    if (!new_acl)
        return;

    if (A->empty()) {
        debugs(28, 0, "Warning: empty ACL: " << A->cfgline);
    }

    if (!A->valid()) {
        fatalf("ERROR: Invalid ACL: %s\n",
               A->cfgline);
    }
