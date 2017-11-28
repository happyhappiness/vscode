SBufList
ACLUserData::dump() const
{
    SBufList sl;

    if (flags.required) {
        sl.push_back(SBuf("REQUIRED"));
        return sl;
    }

    if (flags.case_insensitive)
        sl.push_back(SBuf("-i"));

    sl.insert(sl.end(), userDataNames.begin(), userDataNames.end());

    debugs(28,5, "ACLUserData dump output: " << SBufContainerJoin(userDataNames,SBuf(" ")));
    return sl;
}