static bool
SupportedVersion(const char *vTheir, const char *them)
{
    if (!vTheir || !*vTheir) {
        debugs(93, DBG_CRITICAL, "ERROR: Cannot use " << them <<
               " with libecap prior to v1.0.");
        return false;
    }

    // we support what we are built with
    const SBuf vSupported(LIBECAP_VERSION);
    debugs(93, 2, them << " with libecap v" << vTheir << "; us: v" << vSupported);

    if (EssentialVersion(SBuf(vTheir)) == EssentialVersion(vSupported))
        return true; // their version is supported

    debugs(93, DBG_CRITICAL, "ERROR: Cannot use " << them <<
           " with libecap v" << vTheir <<
           ": incompatible with supported libecap v" << vSupported);
    return false;
}