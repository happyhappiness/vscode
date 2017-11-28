void
BasicUser::updateCached(BasicUser *from)
{
    debugs(29, 9, HERE << "Found user '" << from->username() << "' in the user cache as '" << this << "'");

    if (strcmp(from->passwd, passwd)) {
        debugs(29, 4, HERE << "new password found. Updating in user master record and resetting auth state to unchecked");
        flags.credentials_ok = 0;
        xfree(passwd);
        passwd = from->passwd;
        from->passwd = NULL;
    }

    if (flags.credentials_ok == 3) {
        debugs(29, 4, HERE << "last attempt to authenticate this user failed, resetting auth state to unchecked");
        flags.credentials_ok = 0;
    }
}