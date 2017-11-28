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