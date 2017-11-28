ACL *
ACLLocalIP::clone() const
{
    return new ACLLocalIP(*this);
}