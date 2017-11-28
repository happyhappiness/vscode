bool
Auth::Basic::Config::configured() const
{
    if ((authenticateProgram != NULL) && (authenticateChildren.n_max != 0) &&
            (basicAuthRealm != NULL)) {
        debugs(29, 9, HERE << "returning configured");
        return true;
    }

    debugs(29, 9, HERE << "returning unconfigured");
    return false;
}