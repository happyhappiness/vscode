void
Auth::User::username(char const *aString)
{
    SBuf key;

    if (aString) {
        assert(!username_);
        username_ = xstrdup(aString);
        key = BuildUserKey(username_, requestRealm_);
        // XXX; performance regression. c_str() reallocates, then xstrdup() reallocates
        userKey_ = xstrdup(key.c_str());
    } else {
        safe_free(username_);
        safe_free(userKey_)
    }
}