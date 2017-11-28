CbcPointer<Auth::CredentialsCache>
Auth::Ntlm::User::Cache()
{
    static CbcPointer<Auth::CredentialsCache> p(new Auth::CredentialsCache("ntlm", "GC NTLM user credentials"));
    return p;
}