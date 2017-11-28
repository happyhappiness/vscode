ACLData<HttpRequestMethod> *
ACLMethodData::clone() const
{
    assert(values.empty());
    return new ACLMethodData(*this);
}