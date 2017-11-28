static void
ssl_ask_password(SSL_CTX * context, const char * prompt)
{
    if (Config.Program.ssl_password) {
        SSL_CTX_set_default_passwd_cb(context, ssl_ask_password_cb);
        SSL_CTX_set_default_passwd_cb_userdata(context, (void *)prompt);
    }
}