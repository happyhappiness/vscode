void
Adaptation::AccessRule::parse(ConfigParser &parser)
{
    aclParseAccessLine(parser, &acl);
}