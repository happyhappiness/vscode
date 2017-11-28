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
        debugs(28, 0, "aclParseAclLine: missing ACL name.");
        parser.destruct();
        return;
    }

    if (strlen(t) >= ACL_NAME_SZ) {
        debugs(28, 0, "aclParseAclLine: aclParseAclLine: ACL name '" << t <<
               "' too long, max " << ACL_NAME_SZ - 1 << " characters supported");
        parser.destruct();
        return;
    }

    xstrncpy(aclname, t, ACL_NAME_SZ);
    /* snarf the ACL type */
    char *theType;

    if ((theType = strtok(NULL, w_space)) == NULL) {
        debugs(28, 0, "aclParseAclLine: missing ACL type.");
        parser.destruct();
        return;
    }

    if (!Prototype::Registered (theType)) {
        debugs(28, 0, "aclParseAclLine: Invalid ACL type '" << theType << "'");
        parser.destruct();
        return;
    }

    // Is this ACL going to work?
    if (strcmp(theType, "myip") == 0) {
        http_port_list *p = Config.Sockaddr.http;
        while (p) {
            // Bug 3239: not reliable when there is interception traffic coming
            if (p->intercepted)
                debugs(28, DBG_CRITICAL, "WARNING: 'myip' ACL is not reliable for interception proxies. Please use 'myportname' instead.");
            p = p->next;
        }
    } else if (strcmp(theType, "myport") == 0) {
        http_port_list *p = Config.Sockaddr.http;
        while (p) {
            // Bug 3239: not reliable when there is interception traffic coming
            // Bug 3239: myport - not reliable (yet) when there is interception traffic coming
            if (p->intercepted)
                debugs(28, DBG_CRITICAL, "WARNING: 'myport' ACL is not reliable for interception proxies. Please use 'myportname' instead.");
            p = p->next;
        }
    }

    if ((A = FindByName(aclname)) == NULL) {
        debugs(28, 3, "aclParseAclLine: Creating ACL '" << aclname << "'");
        A = ACL::Factory(theType);
        xstrncpy(A->name, aclname, ACL_NAME_SZ);
        A->cfgline = xstrdup(config_input_line);
        new_acl = 1;
    } else {
        if (strcmp (A->typeString(),theType) ) {
            debugs(28, 0, "aclParseAclLine: ACL '" << A->name << "' already exists with different type.");
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

    /*split the function here */
    A->parse();

    /*
     * Clear AclMatchedName from our temporary hack
     */
    AclMatchedName = NULL;	/* ugly */

    if (!new_acl)
        return;

    if (A->empty()) {
        debugs(28, 0, "Warning: empty ACL: " << A->cfgline);
    }

    if (!A->valid()) {
        fatalf("ERROR: Invalid ACL: %s\n",
               A->cfgline);
    }

    /* append */
    while (*head)
        head = &(*head)->next;

    *head = A;
}