ACLExtUser &
ACLExtUser::operator= (ACLExtUser const &rhs)
{
    data = rhs.data->clone();
    type_ = rhs.type_;
    return *this;
}