void
ACLExternal::parse()
{
    if (data) {
        self_destruct();
        return;
    }

    char *token = ConfigParser::strtokFile();

    if (!token) {
        self_destruct();
        return;
    }

    data = new external_acl_data(find_externalAclHelper(token));

    if (!data->def) {
        delete data;
        self_destruct();
        return;
    }

    // def->name is the name of the external_acl_type.
    // this is the name of the 'acl' directive being tested
    data->name = xstrdup(AclMatchedName);

    while ((token = ConfigParser::strtokFile())) {
        wordlistAdd(&data->arguments, token);
    }
}