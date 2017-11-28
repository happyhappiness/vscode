variable_list *
snmp_confFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    const char *cp = NULL;
    debugs(49, 5, "snmp_confFn: Processing request with magic " << Var->name[8] << "!");
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_CONF]) {

    case CONF_ADMIN:
        Answer = snmp_var_new(Var->name, Var->name_length);
        Answer->type = ASN_OCTET_STR;
        Answer->val_len = strlen(Config.adminEmail);
        Answer->val.string = (u_char *) xstrdup(Config.adminEmail);
        break;

    case CONF_VERSION:
        Answer = snmp_var_new(Var->name, Var->name_length);
        Answer->type = ASN_OCTET_STR;
        Answer->val_len = strlen(APP_SHORTNAME);
        Answer->val.string = (u_char *) xstrdup(APP_SHORTNAME);
        break;

    case CONF_VERSION_ID:
        Answer = snmp_var_new(Var->name, Var->name_length);
        Answer->type = ASN_OCTET_STR;
        Answer->val_len = strlen(VERSION);
        Answer->val.string = (u_char *) xstrdup(VERSION);
        break;

    case CONF_STORAGE:

        switch (Var->name[LEN_SQ_CONF + 1]) {

        case CONF_ST_MMAXSZ:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) (Config.memMaxSize >> 20),
                                          ASN_INTEGER);
            break;

        case CONF_ST_SWMAXSZ:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) (Store::Root().maxSize() >> 10),
                                          ASN_INTEGER);
            break;

        case CONF_ST_SWHIWM:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) Config.Swap.highWaterMark,
                                          ASN_INTEGER);
            break;

        case CONF_ST_SWLOWM:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) Config.Swap.lowWaterMark,
                                          ASN_INTEGER);
            break;

        default:
            *ErrP = SNMP_ERR_NOSUCHNAME;
            break;
        }

        break;

    case CONF_LOG_FAC:
        Answer = snmp_var_new(Var->name, Var->name_length);

        if (!(cp = Debug::debugOptions))
            cp = "None";

        Answer->type = ASN_OCTET_STR;

        Answer->val_len = strlen(cp);

        Answer->val.string = (u_char *) xstrdup(cp);

        break;

    case CONF_UNIQNAME:
        Answer = snmp_var_new(Var->name, Var->name_length);

        cp = uniqueHostname();

        Answer->type = ASN_OCTET_STR;

        Answer->val_len = strlen(cp);

        Answer->val.string = (u_char *) xstrdup(cp);

        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;

        break;
    }

    return Answer;
}