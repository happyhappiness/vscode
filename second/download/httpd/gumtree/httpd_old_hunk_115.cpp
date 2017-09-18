#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Token: eq/ne/ge/gt/le/lt\n",
                    sizeof("     Token: eq/ne/ge/gt/le/lt\n"));
            debug_pos += sizeof("     Token: eq/ne/ge/gt/le/lt\n");
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            /* Percolate upwards */
