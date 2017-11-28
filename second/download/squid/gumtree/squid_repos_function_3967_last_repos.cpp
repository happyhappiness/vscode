ACL *
Acl::TransactionInitiator::clone() const
{
    return new Acl::TransactionInitiator(*this);
}