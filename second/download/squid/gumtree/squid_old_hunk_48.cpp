    // start ICAP request body with encapsulated HTTP headers
    buf.append(httpBuf.content(), httpBuf.contentSize());

    httpBuf.clean();
}

void Adaptation::Icap::ModXact::makeUsernameHeader(const HttpRequest *request, MemBuf &buf)
{
    if (const AuthUserRequest *auth = request->auth_user_request) {
        if (char const *name = auth->username()) {
            const char *value = TheConfig.client_username_encode ?
                                base64_encode(name) : name;
            buf.Printf("%s: %s\r\n", TheConfig.client_username_header,
                       value);
        }
    }
}

void Adaptation::Icap::ModXact::encapsulateHead(MemBuf &icapBuf, const char *section, MemBuf &httpBuf, const HttpMsg *head)
{
    // update ICAP header
    icapBuf.Printf("%s=%d, ", section, (int) httpBuf.contentSize());
