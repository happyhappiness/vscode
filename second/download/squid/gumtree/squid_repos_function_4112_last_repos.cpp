SBufList
ACLHasComponentData::dump() const
{
    SBufList sl;
    if (componentMethods.at(coRequest))
        sl.push_back(RequestStr);
    if (componentMethods.at(coResponse))
        sl.push_back(ResponseStr);
    if (componentMethods.at(coAle))
        sl.push_back(AleStr);
    return sl;
}