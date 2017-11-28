ACL *
ACLMyIP::clone() const
{
    return new ACLMyIP(*this);
}