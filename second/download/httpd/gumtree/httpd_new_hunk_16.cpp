                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Invalid expression \"%s\" in file %s",
                                  expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
