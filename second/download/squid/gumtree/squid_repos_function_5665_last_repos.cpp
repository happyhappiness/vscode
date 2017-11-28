const Acl::Options &
ACLMaxUserIP::options()
{
    static const Acl::BooleanOption BeStrict;
    static const Acl::Options MyOptions = { { "-s", &BeStrict } };
    BeStrict.linkWith(&beStrict);
    return MyOptions;
}