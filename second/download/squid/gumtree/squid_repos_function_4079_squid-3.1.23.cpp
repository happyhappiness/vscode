static bool addCnToRequest(Ssl::X509_REQ_Pointer & request, char const * cn)
{
    // not an Ssl::X509_NAME_Pointer because X509_REQ_get_subject_name()
    // returns a pointer to the existing subject name. Nothing to clean here.
    X509_NAME *name = X509_REQ_get_subject_name(request.get());
    if (!name)
        return false;

    // The second argument of the X509_NAME_add_entry_by_txt declared as
    // "char *" on some OS. Use cn_name to avoid compile warnings.
    static char cn_name[3] = "CN";
    if (!X509_NAME_add_entry_by_txt(name, cn_name, MBSTRING_ASC, (unsigned char *)cn, -1, -1, 0))
        return false;

    return true;
}