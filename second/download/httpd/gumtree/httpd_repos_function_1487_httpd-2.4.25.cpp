static const char *add_alias(cmd_parms *cmd, void *dummy, const char *fake,
        const char *real)
{
    if (real) {

        return add_alias_internal(cmd, dummy, fake, real, 0);

    }
    else {
        alias_dir_conf *dirconf = (alias_dir_conf *) dummy;

        const char *err = ap_check_cmd_context(cmd, NOT_IN_DIRECTORY|NOT_IN_FILES);

        if (err != NULL) {
            return err;
        }

        if (!cmd->path) {
            return "Alias must have two arguments when used globally";
        }

        dirconf->alias =
                ap_expr_parse_cmd(cmd, fake, AP_EXPR_FLAG_STRING_RESULT,
                        &err, NULL);
        if (err) {
            return apr_pstrcat(cmd->temp_pool,
                    "Cannot parse alias expression '", fake, "': ", err,
                    NULL);
        }

        dirconf->handler = cmd->info;
        dirconf->alias_set = 1;

        return NULL;

    }
}