CbcPointer<Auth::CredentialsCache>
Auth::Digest::User::Cache()
{
    static CbcPointer<Auth::CredentialsCache> p(new Auth::CredentialsCache("digest","GC Digest user credentials"));
    return p;
}