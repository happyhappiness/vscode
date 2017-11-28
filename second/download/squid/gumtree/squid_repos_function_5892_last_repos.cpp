const char *
Auth::Ntlm::UserRequest::credentialsStr()
{
    static char buf[MAX_AUTHTOKEN_LEN];
    int printResult;
    if (user()->credentials() == Auth::Pending) {
        printResult = snprintf(buf, sizeof(buf), "YR %s\n", client_blob);
    } else {
        printResult = snprintf(buf, sizeof(buf), "KK %s\n", client_blob);
    }

    // truncation is OK because we are used only for logging
    if (printResult < 0) {
        debugs(29, 2, "Can not build ntlm authentication credentials.");
        buf[0] = '\0';
    } else if (printResult >= (int)sizeof(buf))
        debugs(29, 2, "Ntlm authentication credentials truncated.");

    return buf;
}