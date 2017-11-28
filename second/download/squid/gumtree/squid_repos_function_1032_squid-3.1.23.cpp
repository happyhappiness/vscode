static void
parse_acl_access(acl_access ** head)
{
    aclParseAccessLine(LegacyParser, head);
}