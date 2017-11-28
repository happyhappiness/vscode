SBufList
ACLRegexData::dump() const
{
    SBufList sl;
    int flags = REG_EXTENDED | REG_NOSUB;

    // walk and dump the list
    // keeping the flags values consistent
    for (auto &i : data) {
        if (i.flags != flags) {
            if ((i.flags&REG_ICASE) != 0) {
                sl.emplace_back("-i");
            } else {
                sl.emplace_back("+i");
            }
            flags = i.flags;
        }

        sl.emplace_back(i.c_str());
    }

    return sl;
}