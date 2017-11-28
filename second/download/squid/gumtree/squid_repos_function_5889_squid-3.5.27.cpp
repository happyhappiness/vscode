bool
Auth::Digest::Config::configured() const
{
    if ((authenticateProgram != NULL) &&
            (authenticateChildren.n_max != 0) &&
            !realm.isEmpty() && (noncemaxduration > -1))
        return true;

    return false;
}