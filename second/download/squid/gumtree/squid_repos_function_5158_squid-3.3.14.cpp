bool
ACLProxyAuth::valid () const
{
    if (authenticateSchemeCount() == 0) {
        debugs(28, DBG_CRITICAL, "Can't use proxy auth because no authentication schemes were compiled.");
        return false;
    }

    if (authenticateActiveSchemeCount() == 0) {
        debugs(28, DBG_CRITICAL, "Can't use proxy auth because no authentication schemes are fully configured.");
        return false;
    }

    return true;
}