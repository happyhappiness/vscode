struct snmp_mib_tree *
read_mib(char *filename) {
    FILE *fp;
    struct node *nodes;
    struct snmp_mib_tree *tree;
    char mbuf[256];
    char *p;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        snmplib_debug(1, "init_mib: %s: %s\n", filename, xstrerror());
        return (NULL);
    }
    mbuf[0] = '\0';
    while ((p = fgets(mbuf, 256, fp)) && strncmp(mbuf, "DUMMY",
            strlen("DUMMY")));
    if (!p) {
        snmplib_debug(0, "Bad MIB version or tag missing, install original!\n");
        fclose(fp);
        return NULL;
    }
    if (!strcmp(mbuf, "DUMMY")) {
        snmplib_debug(0, "You need to update your MIB!\n");
        fclose(fp);
        return NULL;
    }
    nodes = parse(fp);
    fclose(fp);
    if (!nodes) {
        snmplib_debug(0, "Mib table is bad.  Exiting\n");
        return NULL;
    }
    tree = build_tree(nodes);
    return (tree);
}