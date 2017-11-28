
    debugs(28, 9, "ACL::FindByName found no match");

    return NULL;
}

ACL *
ACL::Factory (char const *type)
{
    ACL *result = Prototype::Factory (type);

    if (!result)
        fatal ("Unknown acl type in ACL::Factory");

    return result;
}

ACL::ACL() :
    cfgline(nullptr),
    next(nullptr),
    registered(false)
{
    *name = 0;
}

ACL::ACL(const ACLFlag flgs[]) :
    cfgline(NULL),
    next(NULL),
    flags(flgs),
    registered(false)
{
    *name = 0;
}

bool ACL::valid () const
{
    return true;
}

bool
