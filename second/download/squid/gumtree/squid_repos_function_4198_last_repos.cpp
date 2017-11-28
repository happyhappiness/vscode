bool
Acl::OptionNameCmp::operator()(const OptionName a, const OptionName b) const
{
    return strcmp(a, b) < 0;
}