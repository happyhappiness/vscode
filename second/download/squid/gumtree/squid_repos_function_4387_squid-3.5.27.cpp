static const char *getSubjectEntry(X509 *x509, int nid)
{
    static char name[1024] = ""; // stores common name (CN)

    if (!x509)
        return NULL;

    // TODO: What if the entry is a UTF8String? See X509_NAME_get_index_by_NID(3ssl).
    const int nameLen = X509_NAME_get_text_by_NID(
                            X509_get_subject_name(x509),
                            nid,  name, sizeof(name));

    if (nameLen > 0)
        return name;

    return NULL;
}