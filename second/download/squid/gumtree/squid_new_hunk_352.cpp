    if (!result)
        fatal ("Unknown acl type in ACL::Factory");

    return result;
}

ACL::ACL() :
        cfgline(NULL),
        next(NULL)
{
    *name = 0;
}

bool ACL::valid () const
{
    return true;
}

