                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Attribute</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Value</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Last Compare</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Result</b></font></td>"
                             "</tr>\n", r
                            );
                    for (i=0; i < n->compare_cache->size; ++i) {
                        for (p = n->compare_cache->nodes[i]; p != NULL; p = p->next) {

                            (*n->compare_cache->display)(r, n->compare_cache, p->payload);
                        }
                    }
                    ap_rputs("</table>\n</p>\n", r);
                    break;
                case 'd':
                    ap_rputs("<p>\n"
                             "<table border='0'>\n"
                             "<tr bgcolor='#000000'>\n"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Require DN</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Actual DN</b></font></td>"
                             "</tr>\n", r
                            );
                    for (i=0; i < n->dn_compare_cache->size; ++i) {
                        for (p = n->dn_compare_cache->nodes[i]; p != NULL; p = p->next) {

                            (*n->dn_compare_cache->display)(r, n->dn_compare_cache, p->payload);
                        }
                    }
                    ap_rputs("</table>\n</p>\n", r);
                    break;
                default:
                    break;
            }

        }
    }
    else {
        ap_rputs("<p>\n"
                 "<table border='0'>\n"
                 "<tr bgcolor='#000000'>\n"
                 "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Cache Name</b></font></td>"
