bool
BasicUser::valid() const
{
    if (username() == NULL)
        return false;
    if (passwd == NULL)
        return false;
    return true;
}