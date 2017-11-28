                fatalf("'else' without 'if'\n");
        } else if (if_states.empty() || if_states.back()) { // test last if-statement meaning if present
            /* Handle includes here */
            if (tmp_line_len >= 9 && strncmp(tmp_line, "include", 7) == 0 && xisspace(tmp_line[7])) {
                err_count += parseManyConfigFiles(tmp_line + 8, depth + 1);
            } else if (!parse_line(tmp_line)) {
                debugs(3, 0, HERE << cfg_filename << ":" << config_lineno << " unrecognized: '" << tmp_line << "'");
                ++err_count;
            }
        }

        safe_free(tmp_line);
        tmp_line_len = 0;
