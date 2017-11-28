char const *
AuthUserRequest::username() const
{
    if (user())
        return user()->username();
    else
        return NULL;
}