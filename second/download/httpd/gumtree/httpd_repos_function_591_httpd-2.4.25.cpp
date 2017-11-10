static const char *start_ifversion(cmd_parms *cmd, void *mconfig,
                                   const char *arg1, const char *arg2,
                                   const char *arg3)
{
    const char *endp;
    int reverse = 0, done = 0, match = 0, compare;
    const char *p, *error;
    char c;

    /* supplying one argument is possible, we assume an equality check then */
    if (!arg2) {
        arg2 = arg1;
        arg1 = "=";
    }

    /* surrounding quotes without operator */
    if (!arg3 && *arg2 == '>' && !arg2[1]) {
        arg3 = ">";
        arg2 = arg1;
        arg1 = "=";
    }

    /* the third argument makes version surrounding quotes plus operator
     * possible.
     */
    endp = arg2 + strlen(arg2);
    if (   endp == arg2
        || (!(arg3 && *arg3 == '>' && !arg3[1]) && *--endp != '>')) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    p = arg1;
    if (*p == '!') {
        reverse = 1;
        if (p[1]) {
            ++p;
        }
    }

    c = *p++;
    if (!*p || (*p == '=' && !p[1] && c != '~')) {
        if (!httpd_version.major) {
            ap_get_server_revision(&httpd_version);
        }

        done = 1;
        switch (c) {
        case '=':
            /* normal comparison */
            if (*arg2 != '/') {
                compare = compare_version(apr_pstrmemdup(cmd->temp_pool, arg2,
                                                         endp-arg2),
                                          &error);
                if (error) {
                    return error;
                }

                match = !compare;
                break;
            }

            /* regexp otherwise */
            if (endp == ++arg2 || *--endp != '/') {
                return "Missing delimiting / of regular expression.";
            }

        case '~':
            /* regular expression */
            match = match_version(cmd->temp_pool,
                                  apr_pstrmemdup(cmd->temp_pool, arg2,
                                                 endp-arg2),
                                  &error);
            if (error) {
                return error;
            }
            break;

        case '<':
            compare = compare_version(apr_pstrmemdup(cmd->temp_pool, arg2,
                                                     endp-arg2),
                                      &error);
            if (error) {
                return error;
            }

            match = ((-1 == compare) || (*p && !compare));
            break;

        case '>':
            compare = compare_version(apr_pstrmemdup(cmd->temp_pool, arg2,
                                                     endp-arg2),
                                      &error);
            if (error) {
                return error;
            }

            match = ((1 == compare) || (*p && !compare));
            break;

        default:
            done = 0;
            break;
        }
    }

    if (!done) {
        return apr_pstrcat(cmd->pool, "unrecognized operator '", arg1, "'",
                           NULL);
    }

    if ((!reverse && match) || (reverse && !match)) {
        ap_directive_t *parent = NULL;
        ap_directive_t *current = NULL;
        const char *retval;

        retval = ap_build_cont_config(cmd->pool, cmd->temp_pool, cmd,
                                      &current, &parent, "<IfVersion");
        *(ap_directive_t **)mconfig = current;
        return retval;
    }

    *(ap_directive_t **)mconfig = NULL;
    return ap_soak_end_container(cmd, "<IfVersion");
}