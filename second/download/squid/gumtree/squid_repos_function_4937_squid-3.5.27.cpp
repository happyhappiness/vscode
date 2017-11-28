ACLData<Ip::Address> *
ACLASN::clone() const
{
    if (data)
        fatal ("cloning of ACLASN not implemented");

    return new ACLASN(*this);
}