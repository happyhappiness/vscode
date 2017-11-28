void
ACLStringData::parse()
{
    char *t;

    while ((t = strtokFile()))
        values = values->insert(xstrdup(t), splaystrcmp);
}