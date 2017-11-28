void
ACLCertificateData::parse()
{
    char *newAttribute = strtokFile();

    if (!newAttribute)
        self_destruct();

    /* an acl must use consistent attributes in all config lines */
    if (attribute) {
        if (strcasecmp(newAttribute, attribute) != 0)
            self_destruct();
    } else
        attribute = xstrdup(newAttribute);

    values.parse();
}