char const *
Auth::UserRequest::username() const
{
    if (user() != NULL)
        return user()->username();
    else
        return NULL;
}