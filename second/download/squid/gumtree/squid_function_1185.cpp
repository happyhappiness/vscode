void Adaptation::Icap::ModXact::makeUsernameHeader(const HttpRequest *request, MemBuf &buf)
{
#if USE_AUTH
    if (request->auth_user_request != NULL) {
        char const *name = request->auth_user_request->username();
        if (name) {
            const char *value = TheConfig.client_username_encode ? old_base64_encode(name) : name;
            buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
        }
    } else if (request->extacl_user.size() > 0) {
        const char *value = TheConfig.client_username_encode ? old_base64_encode(request->extacl_user.termedBuf()) : request->extacl_user.termedBuf();
        buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
    }
#endif
}