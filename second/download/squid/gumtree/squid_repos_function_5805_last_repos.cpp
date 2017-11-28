const char *
Auth::Basic::UserRequest::credentialsStr()
{
    Auth::Basic::User const *basic_auth = dynamic_cast<Auth::Basic::User const *>(user().getRaw());
    if (basic_auth)
        return basic_auth->passwd;
    return NULL;
}