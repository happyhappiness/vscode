SBufList
ACLNoteData::dump() const
{
    SBufList sl;
    sl.push_back(StringToSBuf(name));
#if __cplusplus >= 201103L
    sl.splice(sl.end(), values->dump());
#else
    // temp is needed until c++11 move constructor
    SBufList temp = values->dump();
    sl.splice(sl.end(), temp);
#endif
    return sl;
}