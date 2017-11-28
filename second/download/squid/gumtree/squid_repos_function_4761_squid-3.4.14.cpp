void
ACLStringData::insert(const char *value)
{
    values = values->insert(xstrdup(value), splaystrcmp);
}