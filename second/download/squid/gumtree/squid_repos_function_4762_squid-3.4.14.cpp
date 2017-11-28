bool
ACLStringData::match(char const *toFind)
{
    if (!values || !toFind)
        return 0;

    debugs(28, 3, "aclMatchStringList: checking '" << toFind << "'");

    values = values->splay((char *)toFind, splaystrcmp);

    debugs(28, 3, "aclMatchStringList: '" << toFind << "' " << (splayLastResult ? "NOT found" : "found"));

    return !splayLastResult;
}