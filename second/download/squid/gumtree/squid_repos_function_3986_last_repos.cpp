SBufList
ACLMethodData::dump() const
{
    SBufList sl;
    for (std::list<HttpRequestMethod>::const_iterator i = values.begin(); i != values.end(); ++i) {
        sl.push_back((*i).image());
    }

    return sl;
}