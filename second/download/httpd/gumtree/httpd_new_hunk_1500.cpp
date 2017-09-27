        }
        conf->qop_list[0] = "none";
        return NULL;
    }

    if (!strcasecmp(op, "auth-int")) {
        return "AuthDigestQop auth-int is not implemented";
    }
    else if (strcasecmp(op, "auth")) {
        return apr_pstrcat(cmd->pool, "Unrecognized qop: ", op, NULL);
    }

    for (cnt = 0; conf->qop_list[cnt] != NULL; cnt++)
