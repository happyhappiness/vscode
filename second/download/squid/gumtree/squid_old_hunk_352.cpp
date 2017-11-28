    if (!result)
        fatal ("Unknown acl type in ACL::Factory");

    return result;
}

ACL::ACL () :cfgline(NULL) {}

bool ACL::valid () const
{
    return true;
}

