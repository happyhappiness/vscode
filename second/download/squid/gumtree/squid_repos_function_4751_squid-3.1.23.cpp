ACLIdent &
ACLIdent::operator= (ACLIdent const &rhs)
{
    data = rhs.data->clone();
    type_ = rhs.type_;
    return *this;
}