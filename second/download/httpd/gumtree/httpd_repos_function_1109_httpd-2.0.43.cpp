static int dsortf(struct ent **e1, struct ent **e2)
{
    struct ent *c1;
    struct ent *c2;
    int result = 0;

    /*
     * First, see if either of the entries is for the parent directory.
     * If so, that *always* sorts lower than anything else.
     */
    if ((*e1)->name[0] == '/') {
        return -1;
    }
    if ((*e2)->name[0] == '/') {
        return 1;
    }
    /* 
     * Now see if one's a directory and one isn't, if we're set
     * isdir for FOLDERS_FIRST. 
     */ 
    if ((*e1)->isdir != (*e2)->isdir) {
        return (*e1)->isdir ? -1 : 1; 
    }
    /*
     * All of our comparisons will be of the c1 entry against the c2 one,
     * so assign them appropriately to take care of the ordering.
     */
    if ((*e1)->ascending) {
        c1 = *e1;
        c2 = *e2;
    }
    else {
        c1 = *e2;
        c2 = *e1;
    }

    switch (c1->key) {
    case K_LAST_MOD:
        if (c1->lm > c2->lm) {
            return 1;
        }
        else if (c1->lm < c2->lm) {
            return -1;
        }
        break;
    case K_SIZE:
        if (c1->size > c2->size) {
            return 1;
        }
        else if (c1->size < c2->size) {
            return -1;
        }
        break;
    case K_DESC:
        if (c1->version_sort) {
            result = apr_strnatcmp(c1->desc ? c1->desc : "",
                                   c2->desc ? c2->desc : "");
        }
        else {
            result = strcmp(c1->desc ? c1->desc : "",
                            c2->desc ? c2->desc : "");
        }
        if (result) {
            return result;
        }
        break;
    }
    if (c1->version_sort) {
        return apr_strnatcmp(c1->name, c2->name);
    }
    else {
        return strcmp(c1->name, c2->name);
    }
}