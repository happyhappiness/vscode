CbcPointer<Auth::CredentialsCache>
Auth::Basic::User::Cache()
{
    static CbcPointer<Auth::CredentialsCache> p(new Auth::CredentialsCache("basic", "GC Basic user credentials"));
    return p;
}