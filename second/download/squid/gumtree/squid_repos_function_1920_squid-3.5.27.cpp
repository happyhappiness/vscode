void
ACLExternal::parse()
{
    char *token;

    if (data)
        self_destruct();

    CBDATA_INIT_TYPE_FREECB(external_acl_data, free_external_acl_data);

    data = cbdataAlloc(external_acl_data);

    token = strtokFile();

    if (!token)
        self_destruct();

    data->def = cbdataReference(find_externalAclHelper(token));

    if (!data->def)
        self_destruct();

    // def->name is the name of the external_acl_type.
    // this is the name of the 'acl' directive being tested
    data->name = xstrdup(AclMatchedName);

    while ((token = strtokFile())) {
        wordlistAdd(&data->arguments, token);
    }
}