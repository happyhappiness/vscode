bool
ACLStringData::match(const SBuf &tf)
{
    if (stringValues.empty() || tf.isEmpty())
        return 0;

    debugs(28, 3, "aclMatchStringList: checking '" << tf << "'");

    bool found = (stringValues.find(tf) != stringValues.end());
    debugs(28, 3, "aclMatchStringList: '" << tf << "' " << (found ? "found" : "NOT found"));

    return found;
}