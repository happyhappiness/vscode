bool
Auth::Basic::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme) const
{
    if (!Auth::Config::dump(entry, name, scheme))
        return false; // not configured

    storeAppendPrintf(entry, "%s basic credentialsttl %d seconds\n", name, (int) credentialsTTL);
    storeAppendPrintf(entry, "%s basic casesensitive %s\n", name, casesensitive ? "on" : "off");
    storeAppendPrintf(entry, "%s basic utf8 %s\n", name, utf8 ? "on" : "off");
    return true;
}