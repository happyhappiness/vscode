bool
AuthDigestConfig::configured() const
{
    if ((authenticate != NULL) &&
            (authenticateChildren != 0) &&
            (digestAuthRealm != NULL) && (noncemaxduration > -1))
        return true;

    return false;
}