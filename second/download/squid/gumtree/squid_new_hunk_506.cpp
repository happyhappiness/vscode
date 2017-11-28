
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

bool
ACL::isProxyAuth() const
{
    return false;
}

/* ACL result caching routines */

int
ACL::matchForCache(ACLChecklist *checklist)
{
    /* This is a fatal to ensure that cacheMatchAcl calls are _only_
