static int
parse_subtree(struct snmp_mib_tree *subtree, char *input, oid *output, int *out_len)
{
    char buf[128], *to = buf;
    u_int subid = 0;
    struct snmp_mib_tree *tp;

    /*
     * No empty strings.  Can happen if there is a trailing '.' or two '.'s
     * in a row, i.e. "..".
     */
    if ((*input == '\0') ||
            (*input == '.'))
        return (0);

    if (xisdigit(*input)) {
        /*
         * Read the number, then try to find it in the subtree.
         */
        while (xisdigit(*input)) {
            subid *= 10;
            subid += *input++ - '0';
        }
        for (tp = subtree; tp; tp = tp->next_peer) {
            if (tp->subid == subid)
                goto found;
        }
        tp = NULL;
    } else {
        /*
         * Read the name into a buffer.
         */
        while ((*input != '\0') &&
                (*input != '.')) {
            *to++ = *input++;
        }
        *to = '\0';

        /*
         * Find the name in the subtree;
         */
        for (tp = subtree; tp; tp = tp->next_peer) {
            if (lc_cmp(tp->label, buf) == 0) {
                subid = tp->subid;
                goto found;
            }
        }

        /*
         * If we didn't find the entry, punt...
         */
        if (tp == NULL) {
            snmplib_debug(0, "sub-identifier not found: %s\n", buf);
            return (0);
        }
    }

found:
    if (subid > (u_int) MAX_SUBID) {
        snmplib_debug(0, "sub-identifier too large: %s\n", buf);
        return (0);
    }
    if ((*out_len)-- <= 0) {
        snmplib_debug(0, "object identifier too long\n");
        return (0);
    }
    *output++ = subid;

    if (*input != '.')
        return (1);
    if ((*out_len =
                parse_subtree(tp ? tp->child_list : NULL, ++input, output, out_len)) == 0)
        return (0);
    return (++*out_len);
}