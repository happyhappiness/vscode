CbcPointer<Auth::CredentialsCache>
Auth::Negotiate::User::Cache()
{
    static CbcPointer<Auth::CredentialsCache> p(new Auth::CredentialsCache("negotiate", "GC Negotiate user credentials"));
    return p;
}