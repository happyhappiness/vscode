static struct snmp_mib_tree *
get_symbol(objid, objidlen, subtree, buf)
oid *objid;
int objidlen;
struct snmp_mib_tree *subtree;
char *buf;
{
    struct snmp_mib_tree *return_tree = NULL;

    for (; subtree; subtree = subtree->next_peer) {
        if (*objid == subtree->subid) {
            strcpy(buf, subtree->label);
            goto found;
        }
    }

    /* subtree not found */
    while (objidlen--) {	/* output rest of name, uninterpreted */
        sprintf(buf, "%u.", *objid++);
        while (*buf)
            buf++;
    }
    *(buf - 1) = '\0';		/* remove trailing dot */
    return NULL;

found:
    if (objidlen > 1) {
        while (*buf)
            buf++;
        *buf++ = '.';
        *buf = '\0';
        return_tree = get_symbol(objid + 1, objidlen - 1, subtree->child_list, buf);
    }
    if (return_tree != NULL)
        return return_tree;
    else
        return subtree;
}