const Acl::Options &
ACLDestinationIP::options()
{
    static const Acl::BooleanOption LookupBan;
    static const Acl::Options MyOptions = { { "-n", &LookupBan } };
    LookupBan.linkWith(&lookupBanned);
    return MyOptions;
}