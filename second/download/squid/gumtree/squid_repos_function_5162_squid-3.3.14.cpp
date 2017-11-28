ACL *
ACLProxyAuth::clone() const
{
    return new ACLProxyAuth(*this);
}