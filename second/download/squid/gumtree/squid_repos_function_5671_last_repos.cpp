int
authenticateSchemeCount(void)
{
    int rv = Auth::Scheme::GetSchemes().size();

    debugs(29, 9, HERE << rv << " active.");

    return rv;
}