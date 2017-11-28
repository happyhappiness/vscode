SBufList
ACLMethodData::dump() const
{
    SBufList sl;
    CbDataList<HttpRequestMethod> *data = values;

    while (data != NULL) {
        sl.push_back(data->element.image());
        data = data->next;
    }

    return sl;
}