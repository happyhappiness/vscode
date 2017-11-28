ACL *
ACLDestinationIP::clone() const
{
    return new ACLDestinationIP(*this);
}