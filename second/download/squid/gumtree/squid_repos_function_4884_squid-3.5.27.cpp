SBufList
ACLHierCodeData::dump() const
{
    SBufList sl;

    for (hier_code iter=HIER_NONE; iter<HIER_MAX; ++iter) {
        if (!values[iter]) continue;
        sl.push_back(SBuf(hier_code_str[iter]));
    }

    return sl;
}