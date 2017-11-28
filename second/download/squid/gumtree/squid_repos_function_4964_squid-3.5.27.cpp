bool
ACLStringData::match(char const *toFind)
{
    if (stringValues.empty() || !toFind)
        return 0;

    SBuf tf(toFind);
    debugs(28, 3, "aclMatchStringList: checking '" << tf << "'");

    bool found = (stringValues.find(tf) != stringValues.end());
    debugs(28, 3, "aclMatchStringList: '" << tf << "' " << (found ? "found" : "NOT found"));

    return found;
}