void
ACL::ParseAclLine(ConfigParser &parser, ACL ** head)
{
    /* we're already using strtok() to grok the line */
    char *t = NULL;
    ACL *A = NULL;
    LOCAL_ARRAY(char, aclname, ACL_NAME_SZ);
    int new_acl = 0;

    /* snarf the ACL name */

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseAclLine: missing ACL name.");
        parser.destruct();
        return;
    }

    if (strlen(t) >= ACL_NAME_SZ) {
        debugs(28, DBG_CRITICAL, "aclParseAclLine: aclParseAclLine: ACL name '" << t <<
               "' too long, max " << ACL_NAME_SZ - 1 << " characters supported");
        parser.destruct();
        return;
    }

    xstrncpy(aclname, t, ACL_NAME_SZ);
    /* snarf the ACL type */
    const char *theType;

    if ((theType = strtok(NULL, w_space)) == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseAclLine: missing ACL type.");
        parser.destruct();
        return;
    }

    // Is this ACL going to work?
    if (strcmp(theType, "myip") == 0) {
        AnyP::PortCfg *p = Config.Sockaddr.http;
        while (p) {
            // Bug 3239: not reliable when there is interception traffic coming
            if (p->flags.natIntercept)
                debugs(28, DBG_CRITICAL, "WARNING: 'myip' ACL is not reliable for interception proxies. Please use 'myportname' instead.");
            p = p->next;
        }
        debugs(28, DBG_IMPORTANT, "UPGRADE: ACL 'myip' type is has been renamed to 'localip' and matches the IP the client connected to.");
        theType = "localip";
    } else if (strcmp(theType, "myport") == 0) {
        AnyP::PortCfg *p = Config.Sockaddr.http;
        while (p) {
            // Bug 3239: not reliable when there is interception traffic coming
            // Bug 3239: myport - not reliable (yet) when there is interception traffic coming
            if (p->flags.natIntercept)
                debugs(28, DBG_CRITICAL, "WARNING: 'myport' ACL is not reliable for interception proxies. Please use 'myportname' instead.");
            p = p->next;
        }
        theType = "localport";
        debugs(28, DBG_IMPORTANT, "UPGRADE: ACL 'myport' type is has been renamed to 'localport' and matches the port the client connected to.");
    }

    if (!Prototype::Registered(theType)) {
        debugs(28, DBG_CRITICAL, "FATAL: Invalid ACL type '" << theType << "'");
        // XXX: make this an ERROR and skip the ACL creation. We *may* die later when its use is attempted. Or may not.
        parser.destruct();
        return;
    }

    if ((A = FindByName(aclname)) == NULL) {
        debugs(28, 3, "aclParseAclLine: Creating ACL '" << aclname << "'");
        A = ACL::Factory(theType);
        A->context(aclname, config_input_line);
        new_acl = 1;
    } else {
        if (strcmp (A->typeString(),theType) ) {
            debugs(28, DBG_CRITICAL, "aclParseAclLine: ACL '" << A->name << "' already exists with different type.");
            parser.destruct();
            return;
        }

        debugs(28, 3, "aclParseAclLine: Appending to '" << aclname << "'");
        new_acl = 0;
    }

    /*
     * Here we set AclMatchedName in case we need to use it in a
     * warning message in aclDomainCompare().
     */
    AclMatchedName = A->name;	/* ugly */

    A->flags.parseFlags();

    /*split the function here */
    A->parse();

    /*
     * Clear AclMatchedName from our temporary hack
     */
    AclMatchedName = NULL;	/* ugly */

    if (!new_acl)
        return;

    if (A->empty()) {
        debugs(28, DBG_CRITICAL, "Warning: empty ACL: " << A->cfgline);
    }

    if (!A->valid()) {
        fatalf("ERROR: Invalid ACL: %s\n",
               A->cfgline);
    }

    // add to the global list for searching explicit ACLs by name
    assert(head && *head == Config.aclList);
    A->next = *head;
    *head = A;

    // register for centralized cleanup
    aclRegister(A);
}