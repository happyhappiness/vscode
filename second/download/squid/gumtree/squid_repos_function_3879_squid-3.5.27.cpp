void
Adaptation::AccessRule::parse(ConfigParser &parser)
{
    aclParseAccessLine("adaptation_access", parser, &acl);
}