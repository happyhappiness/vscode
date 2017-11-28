bool
ACLExternal::valid () const
{
    if (data->def->require_auth) {
        if (authenticateSchemeCount() == 0) {
            debugs(28, 0, "Can't use proxy auth because no authentication schemes were compiled.");
            return false;
        }

        if (authenticateActiveSchemeCount() == 0) {
            debugs(28, 0, "Can't use proxy auth because no authentication schemes are fully configured.");
            return false;
        }
    }

    return true;
}