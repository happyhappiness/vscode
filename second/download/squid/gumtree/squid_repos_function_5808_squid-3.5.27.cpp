int
Auth::Basic::UserRequest::authenticated() const
{
    Auth::Basic::User const *basic_auth = dynamic_cast<Auth::Basic::User const *>(user().getRaw());

    if (basic_auth && basic_auth->authenticated())
        return 1;

    return 0;
}