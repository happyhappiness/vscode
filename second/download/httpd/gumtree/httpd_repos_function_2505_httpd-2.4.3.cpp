char *util_ald_cache_display(request_rec *r, util_ldap_state_t *st)
{
    unsigned long i,j;
    char *buf, *t1, *t2, *t3;
    char *id1, *id2, *id3;
    char *argfmt = "cache=%s&id=%d&off=%d";
    char *scanfmt = "cache=%4s&id=%u&off=%u%1s";
    apr_pool_t *pool = r->pool;
    util_cache_node_t *p = NULL;
    util_url_node_t *n = NULL;

    util_ald_cache_t *util_ldap_cache = st->util_ldap_cache;


    if (!util_ldap_cache) {
        ap_rputs("<tr valign='top'><td nowrap colspan=7>Cache has not been enabled/initialised.</td></tr>", r);
        return NULL;
    }

    if (r->args && strlen(r->args)) {
        char cachetype[5], lint[2];
        unsigned int id, off;
        char date_str[APR_CTIME_LEN];

        if ((3 == sscanf(r->args, scanfmt, cachetype, &id, &off, lint)) &&
            (id < util_ldap_cache->size)) {

            if ((p = util_ldap_cache->nodes[id]) != NULL) {
                n = (util_url_node_t *)p->payload;
                buf = (char*)n->url;
            }
            else {
                buf = "";
            }

            ap_rprintf(r,
                       "<p>\n"
                       "<table border='0'>\n"
                       "<tr>\n"
                       "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Cache Name:</b></font></td>"
                       "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%s (%s)</b></font></td>"
                       "</tr>\n"
                       "</table>\n</p>\n",
                       buf,
                       cachetype[0] == 'm'? "Main" :
                       (cachetype[0] == 's' ? "Search" :
                        (cachetype[0] == 'c' ? "Compares" : "DNCompares")));

            switch (cachetype[0]) {
                case 'm':
                    if (util_ldap_cache->marktime) {
                        apr_ctime(date_str, util_ldap_cache->marktime);
                    }
                    else
                        date_str[0] = 0;

                    ap_rprintf(r,
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
                               date_str);

                    ap_rputs("<p>\n"
                             "<table border='0'>\n"
                             "<tr bgcolor='#000000'>\n"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>LDAP URL</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Size</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Max Entries</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b># Entries</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Full Mark</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Full Mark Time</b></font></td>"
                             "</tr>\n", r
                            );
                    for (i=0; i < util_ldap_cache->size; ++i) {
                        for (p = util_ldap_cache->nodes[i]; p != NULL; p = p->next) {

                            (*util_ldap_cache->display)(r, util_ldap_cache, p->payload);
                        }
                    }
                    ap_rputs("</table>\n</p>\n", r);


                    break;
                case 's':
                    ap_rputs("<p>\n"
                             "<table border='0'>\n"
                             "<tr bgcolor='#000000'>\n"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>LDAP Filter</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>User Name</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Last Bind</b></font></td>"
                             "</tr>\n", r
                            );
                    if (n) {
                        for (i=0; i < n->search_cache->size; ++i) {
                            for (p = n->search_cache->nodes[i]; p != NULL; p = p->next) {

                                (*n->search_cache->display)(r, n->search_cache, p->payload);
                            }
                        }
                    }
                    ap_rputs("</table>\n</p>\n", r);
                    break;
                case 'c':
                    ap_rputs("<p>\n"
                             "<table border='0'>\n"
                             "<tr bgcolor='#000000'>\n"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>DN</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Attribute</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Value</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Last Compare</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Result</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Sub-groups?</b></font></td>"
                             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>S-G Checked?</b></font></td>"
                             "</tr>\n", r
                            );
                    if (n) {
                        for (i=0; i < n->compare_cache->size; ++i) {
                            for (p = n->compare_cache->nodes[i]; p != NULL; p = p->next) {

                                (*n->compare_cache->display)(r, n->compare_cache, p->payload);
                            }
                        }
                    }
                    ap_rputs("</table>\n</p>\n", r);
                    break;
                case 'd':
                    ap_rputs("<p>\n"
                         