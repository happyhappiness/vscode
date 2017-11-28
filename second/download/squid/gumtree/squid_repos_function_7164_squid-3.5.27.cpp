Mgr::QueryParams::Params::const_iterator
Mgr::QueryParams::find(const String& name) const
{
    Must(name.size() != 0);
    Params::const_iterator iter = params.begin();
    for ( ; iter != params.end(); ++iter) {
        if (name.caseCmp(iter->first) == 0)
            break;
    }
    return iter;
}