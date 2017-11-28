bool
Auth::Digest::Config::configured() const
{
    if ((authenticateProgram != NULL) &&
            (authenticateChildren.n_max != 0) &&
            (digestAuthRealm != NULL) && (noncemaxduration > -1))
        return true;

    return false;
}