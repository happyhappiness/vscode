void
digestScheme::done()
{
    /** \todo this should be a Config call. */

    if (digestauthenticators)
        helperShutdown(digestauthenticators);

    if (DigestFieldsInfo) {
        httpHeaderDestroyFieldsInfo(DigestFieldsInfo, DIGEST_ENUM_END);
        DigestFieldsInfo = NULL;
    }

    authdigest_initialised = 0;

    if (!shutting_down) {
        authenticateDigestNonceReconfigure();
        return;
    }

    if (digestauthenticators) {
        helperFree(digestauthenticators);
        digestauthenticators = NULL;
    }

    authDigestUserShutdown();
    authenticateDigestNonceShutdown();
    debugs(29, 2, "authenticateDigestDone: Digest authentication shut down.");
}