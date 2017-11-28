ACL *
ACLExternal::clone() const
{
    return new ACLExternal(*this);
}