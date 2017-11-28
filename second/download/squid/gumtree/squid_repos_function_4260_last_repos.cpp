ACLData<err_type> *
ACLSquidErrorData::clone() const
{
    if (!errors.empty())
        fatal("ACLSquidError::clone: attempt to clone used ACL");

    return new ACLSquidErrorData (*this);
}