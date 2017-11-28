
        ;	/* find the tail */
    *T = A;
}

void
aclParseAccessLine(ConfigParser &parser, acl_access ** head)
{
    char *t = NULL;
    acl_access *A = NULL;
    acl_access *B = NULL;
    acl_access **T = NULL;

    /* first expect either 'allow' or 'deny' */

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: missing 'allow' or 'deny'.");
        return;
    }

    A = new acl_access;

    if (!strcmp(t, "allow"))
        A->allow = ACCESS_ALLOWED;
    else if (!strcmp(t, "deny"))
        A->allow = ACCESS_DENIED;
    else {
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: expecting 'allow' or 'deny', got '" << t << "'.");
        delete A;
        return;
    }

    aclParseAclList(parser, &A->aclList);

    if (A->aclList == NULL) {
        debugs(28, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: Access line contains no ACL's, skipping");
        delete A;
        return;
    }

    A->cfgline = xstrdup(config_input_line);
    /* Append to the end of this list */

    for (B = *head, T = head; B; T = &B->next, B = B->next);
    *T = A;

    /* We lock _acl_access structures in ACLChecklist::matchNonBlocking() */
}

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

/*********************/
/* Destroy functions */
/*********************/

void
aclDestroyAcls(ACL ** head)
{
    ACL *next = NULL;

    debugs(28, 8, "aclDestroyACLs: invoked");

    for (ACL *a = *head; a; a = next) {
        next = a->next;
        delete a;
    }

    *head = NULL;
}

void
aclDestroyAclList(ACLList ** head)
{
    ACLList *l;
    debugs(28, 8, "aclDestroyAclList: invoked");

    for (l = *head; l; l = *head) {
        *head = l->next;
        delete l;
    }
}

void
aclDestroyAccessList(acl_access ** list)
{
    acl_access *l = NULL;
    acl_access *next = NULL;

    for (l = *list; l; l = next) {
        debugs(28, 3, "aclDestroyAccessList: '" << l->cfgline << "'");
        next = l->next;
        aclDestroyAclList(&l->aclList);
        safe_free(l->cfgline);
        cbdataFree(l);
    }

    *list = NULL;
}

/* maex@space.net (06.09.1996)
 *    destroy an AclDenyInfoList */

