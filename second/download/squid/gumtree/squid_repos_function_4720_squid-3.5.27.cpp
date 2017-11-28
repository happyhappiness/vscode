SBufList
ACLHTTPHeaderData::dump() const
{
    SBufList sl;
    sl.push_back(SBuf(hdrName));
#if __cplusplus >= 201103L
    sl.splice(sl.end(), regex_rule->dump());
#else
    // temp is needed until c++11 move-constructor
    SBufList temp = regex_rule->dump();
    sl.splice(sl.end(), temp);
#endif
    return sl;
}