static int ssl_init_FindCAList_X509NameCmp(char **a, char **b)
{
    return(X509_NAME_cmp((void*)*a, (void*)*b));
}