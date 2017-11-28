ACLData<HttpRequestMethod> *
ACLMethodData::clone() const
{
    assert (!values);
    return new ACLMethodData(*this);
}