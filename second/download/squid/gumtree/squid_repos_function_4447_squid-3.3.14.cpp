void
aclParseAclList(ConfigParser &parser, ACLList ** head)
{
    ACLList **Tail = head;	/* sane name in the use below */
    ACL *a = NULL;
    char *t;

    /* next expect a list of ACL names, possibly preceeded
     * by '!' for negation */

    while ((t = strtok(NULL, w_space))) {
        ACLList *L = new ACLList;

        if (*t == '!') {
            L->negated (true);
            ++t;
        }

        debugs(28, 3, "aclParseAclList: looking for ACL name '" << t << "'");
        a = ACL::FindByName(t);

        if (a == NULL) {
            debugs(28, DBG_CRITICAL, "aclParseAclList: ACL name '" << t << "' not found.");
            delete L;
            parser.destruct();
            continue;
        }

        L->_acl = a;
        *Tail = L;
        Tail = &L->next;
    }
}