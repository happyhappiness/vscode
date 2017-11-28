int
authenticateSchemeCount(void)
{
    int rv = AuthScheme::Schemes().size();

    debugs(29, 9, "authenticateSchemeCount: " << rv << " active.");

    return rv;
}