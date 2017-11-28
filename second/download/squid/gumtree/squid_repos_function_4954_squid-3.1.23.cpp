int
AuthDigestUserRequest::authenticated() const
{
    if (credentials() == Ok)
        return 1;

    return 0;
}