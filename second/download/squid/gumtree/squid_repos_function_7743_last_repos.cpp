static struct snmp_mib_tree *
find_rfc1066_mib(struct snmp_mib_tree *root) {
    oid *op = RFC1066_MIB;
    struct snmp_mib_tree *tp;
    int len;

    for (len = sizeof(RFC1066_MIB) / sizeof(oid); len; len--, op++) {
        for (tp = root; tp; tp = tp->next_peer) {
            if (tp->subid == *op) {
                root = tp->child_list;
                break;
            }
        }
        if (tp == NULL)
            return NULL;
    }
    return root;
}