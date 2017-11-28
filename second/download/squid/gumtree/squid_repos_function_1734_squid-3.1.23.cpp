void
ACLExternal::parse()
{
    char *token;

    if (data)
        self_destruct();

    CBDATA_INIT_TYPE_FREECB(external_acl_data, free_external_acl_data);

    data = cbdataAlloc(external_acl_data);

    token = strtok(NULL, w_space);

    if (!token)
        self_destruct();

    data->def = cbdataReference(find_externalAclHelper(token));

    if (!data->def)
        self_destruct();

    while ((token = strtokFile())) {
        wordlistAdd(&data->arguments, token);
    }
}