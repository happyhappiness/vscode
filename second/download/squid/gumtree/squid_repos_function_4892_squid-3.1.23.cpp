bool
BasicUser::decodeCleartext()
{
    char *sent_auth = NULL;

    /* username and password */
    sent_auth = xstrdup(httpAuthHeader);

    /* Trim trailing \n before decoding */
    strtok(sent_auth, "\n");

    cleartext = uudecode(sent_auth);

    safe_free(sent_auth);

    if (!cleartext)
        return false;

    /*
     * Don't allow NL or CR in the credentials.
     * Oezguer Kesim <oec@codeblau.de>
     */
    debugs(29, 9, HERE << "'" << cleartext << "'");

    if (strcspn(cleartext, "\r\n") != strlen(cleartext)) {
        debugs(29, 1, HERE << "bad characters in authorization header '" << httpAuthHeader << "'");
        safe_free(cleartext);
        return false;
    }
    return true;
}