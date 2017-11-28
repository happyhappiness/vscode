void
Adaptation::Config::ParseAccess(ConfigParser &parser)
{
    String groupId = ConfigParser::NextToken();
    AccessRule *r;
    if (!(r=FindRuleByGroupId(groupId))) {
        r = new AccessRule(groupId);
        AllRules().push_back(r);
    }
    r->parse(parser);
}