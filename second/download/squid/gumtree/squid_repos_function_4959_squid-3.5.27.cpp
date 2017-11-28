SBufList
ACLProtocolData::dump() const
{
    SBufList sl;
    CbDataList<AnyP::ProtocolType> *data = values;

    while (data != NULL) {
        sl.push_back(SBuf(AnyP::ProtocolType_str[data->element]));
        data = data->next;
    }

    return sl;
}