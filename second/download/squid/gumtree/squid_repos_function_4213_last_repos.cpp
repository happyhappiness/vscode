void
ACLExtUser::parseFlags()
{
    ParseFlags(Acl::NoOptions(), data->supportedFlags());
}