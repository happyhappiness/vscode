ap_rputs(apr_psprintf(r->pool, 
                            "<p>\n"
                            "<table border='0'>\n"
                            "<tr>\n"
                            "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Size:</b></font></td>"
                            "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%ld</b></font></td>"
                            "</tr>\n"
                            "<tr>\n"
                            "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Max Entries:</b></font></td>"
                            "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%ld</b></font></td>"
                            "</tr>\n"
                            "<tr>\n"
                            "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b># Entries:</b></font></td>"
                            "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%ld</b></font></td>"
                            "</tr>\n"
                            "<tr>\n"
                            "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Full Mark:</b></font></td>"
                            "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%ld</b></font></td>"
                            "</tr>\n"
                            "<tr>\n"
                            "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Full Mark Time:</b></font></td>"
                            "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%s</b></font></td>"
                            "</tr>\n"
                            "</table>\n</p>\n",
                        util_ldap_cache->size,
                        util_ldap_cache->maxentries,
                        util_ldap_cache->numentries,
                        util_ldap_cache->fullmark,
                        date_str), r);