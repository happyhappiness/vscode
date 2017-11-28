void
Auth::Basic::User::updateCached(Auth::Basic::User *from)
{
    debugs(29, 9, HERE << "Found user '" << from->username() << "' already in the user cache as '" << this << "'");

    assert(strcmp(from->username(), username()) == 0);

    if (strcmp(from->passwd, passwd)) {
        debugs(29, 4, HERE << "new password found. Updating in user master record and resetting auth state to unchecked");
        credentials(Auth::Unchecked);
        xfree(passwd);
        passwd = from->passwd;
        from->passwd = NULL;
    }

    if (credentials() == Auth::Failed) {
        debugs(29, 4, HERE << "last attempt to authenticate this user failed, resetting auth state to unchecked");
        credentials(Auth::Unchecked);
    }
}