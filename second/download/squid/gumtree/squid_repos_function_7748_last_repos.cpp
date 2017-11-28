void
sprint_objid(buf, objid, objidlen)
char *buf;
oid *objid;
int objidlen;       /* number of subidentifiers */
{
    struct snmp_mib_tree *subtree = Mib;

    *buf = '.';         /* this is a fully qualified name */
    get_symbol(objid, objidlen, subtree, buf + 1);
}