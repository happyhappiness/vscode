                        while (cmd) {
                            if (cmd->name) {
                                ap_rprintf(r, "<dd><tt>%s%s - <i>",
                                           ap_escape_html(r->pool, cmd->name),
                                           cmd->name[0] == '<' ? "&gt;" : "");
                                if (cmd->errmsg) {
                                    ap_rputs(cmd->errmsg, r);
                                }
                                ap_rputs("</i></tt></dd>\n", r);
                            }
                            else {
                                break;
                            }
