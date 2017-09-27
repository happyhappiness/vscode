        ret[outlen] = '\0';
    }

    return ret;
}

static const char *ssi_parse_string(request_rec *r, const char *in)
{
    include_ctx_t *ctx = ap_get_module_config(r->request_config,
                                              &include_module);
    return ap_ssi_parse_string(ctx, in, NULL, 0, SSI_EXPAND_DROP_NAME);
}
static int ssi_access(request_rec *r, ap_parse_node_t *current,
                      string_func_t parse_string)
{
    request_rec *rr;
    include_ctx_t *ctx = ap_get_module_config(r->request_config,
                                              &include_module);

    /* if this arg isn't -A, just return */
    if (current->token.type != TOKEN_ACCESS || current->token.value[0] != 'A') {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Unsupported option -%s in file %s",
                      current->token.value, r->filename);
        return 1;
    }
    if (current->left || !current->right ||
        (current->right->token.type != TOKEN_STRING &&
         current->right->token.type != TOKEN_RE)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "Invalid expression in file %s: Token '-A' must be followed by a URI string.",
                    r->filename);
        return 1;    /* was_error */
    }
    current->right->token.value =
        ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
                            SSI_EXPAND_DROP_NAME);
    rr = ap_sub_req_lookup_uri(current->right->token.value, r, NULL);
    /* 400 and higher are considered access denied */
    if (rr->status < HTTP_BAD_REQUEST) {
        current->value = 1;
    }
    else {
        current->value = 0;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rr->status, r,
                      "mod_include: The tested "
                      "subrequest -A \"%s\" returned an error code.",
                      current->right->token.value);
    }
    ap_destroy_sub_req(rr);
    return 0;
}

/*
 * +-------------------------------------------------------+
 * |                                                       |
 * |                    Action Handlers
