
    debugs(28, 9, "ACL::FindByName found no match");

    return NULL;
}

ACL::ACL() :
    cfgline(nullptr),
    next(nullptr),
    registered(false)
{
    *name = 0;
}

bool ACL::valid () const
{
    return true;
}

bool
