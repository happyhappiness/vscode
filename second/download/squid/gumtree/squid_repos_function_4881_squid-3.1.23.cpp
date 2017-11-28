int
AuthBasicUserRequest::authenticated() const
{
    BasicUser const *basic_auth = dynamic_cast<BasicUser const *>(user());

    if (basic_auth && basic_auth->authenticated())
        return 1;

    return 0;
}