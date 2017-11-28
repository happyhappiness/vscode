const Acl::Options &
ACLDestinationDomainStrategy::options()
{
    static const Acl::BooleanOption LookupBanFlag;
    static const Acl::Options MyOptions = { { "-n", &LookupBanFlag } };
    LookupBanFlag.linkWith(&lookupBanned);
    return MyOptions;
}