ACL *
ACLExtUser::clone() const
{
    return new ACLExtUser(*this);
}