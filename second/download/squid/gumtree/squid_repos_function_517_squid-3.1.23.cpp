static
#endif
struct snmp_mib_tree *
build_tree(struct node *nodes) {
    struct node *np;
    struct snmp_mib_tree *tp;
    int bucket, nodes_left = 0;

    /* build root node */
    tp = (struct snmp_mib_tree *) xmalloc(sizeof(struct snmp_mib_tree));
    tp->parent = NULL;
    tp->next_peer = NULL;
    tp->child_list = NULL;
    tp->enums = NULL;
    strcpy(tp->label, "iso");
    tp->subid = 1;
    tp->type = 0;
    build_translation_table();
    /* grow tree from this root node */
    init_node_hash(nodes);
    /* XXX nodes isn't needed in do_subtree() ??? */
    do_subtree(tp, &nodes);
#ifdef TEST
    print_subtree(tp, 0);
#endif /* TEST */
    /* If any nodes are left, the tree is probably inconsistent */
    for (bucket = 0; bucket < NHASHSIZE; bucket++) {
        if (nbuckets[bucket]) {
            nodes_left = 1;
            break;
        }
    }
    if (nodes_left) {
        snmplib_debug(0, "The mib description doesn't seem to be consistent.\n");
        snmplib_debug(0, "Some nodes couldn't be linked under the \"iso\" tree.\n");
        snmplib_debug(0, "these nodes are left:\n");
        for (bucket = 0; bucket < NHASHSIZE; bucket++) {
            for (np = nbuckets[bucket]; np; np = np->next)
                snmplib_debug(5, "%s ::= { %s %d } (%d)\n", np->label, np->parent, np->subid,
                              np->type);
        }
    }
    return tp;
}