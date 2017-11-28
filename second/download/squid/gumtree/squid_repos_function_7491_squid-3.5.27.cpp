void
print_objid(objid, objidlen)
oid *objid;
int objidlen;       /* number of subidentifiers */
{
    char buf[256];
    struct snmp_mib_tree *subtree = Mib;

    *buf = '.';         /* this is a fully qualified name */
    get_symbol(objid, objidlen, subtree, buf + 1);
    snmplib_debug(7, "%s\n", buf);

}