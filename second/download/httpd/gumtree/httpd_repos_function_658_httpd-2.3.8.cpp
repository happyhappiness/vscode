static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a, 
                                           const X509_NAME * const *b)
{
    return(X509_NAME_cmp(*a, *b));
}