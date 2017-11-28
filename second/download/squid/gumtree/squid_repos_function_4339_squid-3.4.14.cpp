Ssl::Helper * Ssl::Helper::GetInstance()
{
    static Ssl::Helper sslHelper;
    return &sslHelper;
}