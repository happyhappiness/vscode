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

    /* names may identical when treated case-insensitively,
     * so always fall back on strcmp() flavors to put entries
     * in deterministic order.  This means that 'ABC' and 'abc'
     * will always appear in the same order, rather than
     * variably between 'ABC abc' and 'abc ABC' order.
     */

    if (c1->version_sort) {
        if (c1->ignore_case) {
            result = apr_strnatcasecmp (c1->name, c2->name);
        }
        if (!result) {
            result = apr_strnatcmp(c1->name, c2->name);
        }
    }

    /* The names may be identical in respects other other than
     * filename case when strnatcmp is used above, so fall back
     * to strcmp on conflicts so that fn1.01.zzz and fn1.1.zzz
     * are also sorted in a deterministic order.
     */

    if (!result && c1->ignore_case) {
        result = strcasecmp (c1->name, c2->name);
    }

    if (!result) {
        result = strcmp (c1->name, c2->name);
    }

    return result;
}