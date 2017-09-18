            memcpy(&debug[debug_pos], "     Evaluate and/or\n",
                    sizeof("     Evaluate and/or\n"));
            debug_pos += sizeof("     Evaluate and/or\n");
#endif
            if (current->left  == (struct parse_node *) NULL ||
                current->right == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            if (!current->left->done) {
