
        ;	/* find the tail */
    *T = A;
}

void
aclParseAccessLine(const char *directive, ConfigParser &, acl_access **treep)
{
    /* first expect either 'allow' or 'deny' */
    const char *t = ConfigParser::strtokFile();

    if (!t) {
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: missing 'allow' or 'deny'.");
        return;
    }

    allow_t action = ACCESS_DUNNO;
    if (!strcmp(t, "allow"))
        action = ACCESS_ALLOWED;
    else if (!strcmp(t, "deny"))
        action = ACCESS_DENIED;
    else {
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: expecting 'allow' or 'deny', got '" << t << "'.");
        return;
    }

    const int ruleId = ((treep && *treep) ? (*treep)->childrenCount() : 0) + 1;
    MemBuf ctxBuf;
    ctxBuf.init();
    ctxBuf.Printf("%s#%d", directive, ruleId);
    ctxBuf.terminate();

    Acl::AndNode *rule = new Acl::AndNode;
    rule->context(ctxBuf.content(), config_input_line);
    rule->lineParse();
    if (rule->empty()) {
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseAccessLine: Access line contains no ACL's, skipping");
        delete rule;
        return;
    }

    /* Append to the end of this list */

    assert(treep);
    if (!*treep) {
        *treep = new Acl::Tree;
        (*treep)->context(directive, config_input_line);
    }

    (*treep)->add(rule, action);

    /* We lock _acl_access structures in ACLChecklist::matchNonBlocking() */
}

// aclParseAclList does not expect or set actions (cf. aclParseAccessLine)
void
aclParseAclList(ConfigParser &, Acl::Tree **treep, const char *label)
{
    // accomodate callers unable to convert their ACL list context to string
    if (!label)
        label = "...";

    MemBuf ctxLine;
    ctxLine.init();
    ctxLine.Printf("(%s %s line)", cfg_directive, label);
    ctxLine.terminate();

    Acl::AndNode *rule = new Acl::AndNode;
    rule->context(ctxLine.content(), config_input_line);
    rule->lineParse();

    MemBuf ctxTree;
    ctxTree.init();
    ctxTree.Printf("%s %s", cfg_directive, label);
    ctxTree.terminate();

    // We want a cbdata-protected Tree (despite giving it only one child node).
    Acl::Tree *tree = new Acl::Tree;
    tree->add(rule);
    tree->context(ctxTree.content(), config_input_line);

    assert(treep);
    assert(!*treep);
    *treep = tree;
}

void
aclRegister(ACL *acl)
{
    if (!acl->registered) {
        if (!RegisteredAcls)
            RegisteredAcls = new AclSet;
        RegisteredAcls->insert(acl);
        acl->registered = true;
    }
}

/// remove registered acl from the centralized deletion set
static
void
aclDeregister(ACL *acl)
{
    if (acl->registered) {
        if (RegisteredAcls)
            RegisteredAcls->erase(acl);
        acl->registered = false;
    }
}

/*********************/
/* Destroy functions */
/*********************/

/// called to delete ALL Acls.
void
aclDestroyAcls(ACL ** head)
{
    *head = NULL; // Config.aclList
    if (AclSet *acls = RegisteredAcls) {
        debugs(28, 8, "deleting all " << acls->size() << " ACLs");
        while (!acls->empty()) {
            ACL *acl = *acls->begin();
            // We use centralized deletion (this function) so ~ACL should not
            // delete other ACLs, but we still deregister first to prevent any
            // accesses to the being-deleted ACL via RegisteredAcls.
            assert(acl->registered); // make sure we are making progress
            aclDeregister(acl);
            delete acl;
        }
    }
}

void
aclDestroyAclList(ACLList **list)
{
    debugs(28, 8, "aclDestroyAclList: invoked");
    assert(list);
    delete *list;
    *list = NULL;
}

void
aclDestroyAccessList(acl_access ** list)
{
    assert(list);
    if (*list)
        debugs(28, 3, "destroying: " << *list << ' ' << (*list)->name);
    delete *list;
    *list = NULL;
}

/* maex@space.net (06.09.1996)
 *    destroy an AclDenyInfoList */

