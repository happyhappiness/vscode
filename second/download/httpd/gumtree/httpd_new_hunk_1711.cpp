
            if (current->token.type == TOKEN_NOT) {
                current->value = !current->value;
            }
            break;

        case TOKEN_ACCESS:
            if (current->left || !current->right ||
                (current->right->token.type != TOKEN_STRING &&
                 current->right->token.type != TOKEN_RE)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s: Token '-A' must be followed by a URI string.",
                            expr, r->filename);
                *was_error = 1;
                return 0;
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
            break;

        case TOKEN_RE:
            if (!error) {
                error = "No operator before regex in expr \"%s\" in file %s";
            }
        case TOKEN_LBRACE:
            if (!error) {
