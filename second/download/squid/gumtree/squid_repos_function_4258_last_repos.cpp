void
ACLSquidErrorData::parse()
{
    while (char *token = ConfigParser::NextToken()) {
        err_type err = errorTypeByName(token);

        if (err < ERR_MAX)
            errors.push_back(err);
        else {
            debugs(28, DBG_CRITICAL, "FATAL: Invalid squid error name");
            if (!opt_parse_cfg_only)
                self_destruct();
        }
    }
}