void
Auth::User::username(char const *aString)
{
    if (aString) {
        assert(!username_);
        username_ = xstrdup(aString);
        // NP: param #2 is working around a c_str() data-copy performance regression
        userKey_ = BuildUserKey(username_, (!requestRealm_.isEmpty() ? requestRealm_.c_str() : NULL));
    } else {
        safe_free(username_);
        userKey_.clear();
    }
}