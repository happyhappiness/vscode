ACLData<HttpHeader*> *
ACLHTTPHeaderData::clone() const
{
    /* Header's don't clone yet. */
    ACLHTTPHeaderData * result = new ACLHTTPHeaderData;
    result->regex_rule = regex_rule->clone();
    result->hdrId = hdrId;
    result->hdrName = hdrName;
    return result;
}