static void
parse_acl_access(acl_access ** head)
{
    aclParseAccessLine(cfg_directive, LegacyParser, head);
}