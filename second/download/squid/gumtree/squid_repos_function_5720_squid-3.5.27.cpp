int
authenticateActiveSchemeCount(void)
{
    int rv = 0;

    for (Auth::ConfigVector::iterator i = Auth::TheConfig.begin(); i != Auth::TheConfig.end(); ++i)
        if ((*i)->configured())
            ++rv;

    debugs(29, 9, HERE << rv << " active.");

    return rv;
}