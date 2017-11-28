const char *
Auth::Negotiate::UserRequest::credentialsStr()
{
    static char buf[MAX_AUTHTOKEN_LEN];
    int printResult = 0;
    if (user()->credentials() == Auth::Pending) {
        printResult = snprintf(buf, sizeof(buf), "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
    } else {
        printResult = snprintf(buf, sizeof(buf), "KK %s\n", client_blob);
    }

    // truncation is OK because we are used only for logging
    if (printResult < 0) {
        debugs(29, 2, "Can not build negotiate authentication credentials.");
        buf[0] = '\0';
    } else if (printResult >= (int)sizeof(buf))
        debugs(29, 2, "Negotiate authentication credentials truncated.");

    return buf;
}