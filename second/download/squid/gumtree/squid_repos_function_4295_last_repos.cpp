SBufList
ACLProtocolData::dump() const
{
    SBufList sl;
    for (std::list<AnyP::ProtocolType>::const_iterator itr = values.begin(); itr != values.end(); ++itr) {
        sl.push_back(SBuf(AnyP::ProtocolType_str[*itr]));
    }

    return sl;
}