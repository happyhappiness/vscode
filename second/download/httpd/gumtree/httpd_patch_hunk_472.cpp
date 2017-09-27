                              "<tr bgcolor='#000000'>\n"
                              "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>LDAP Filter</b></font></td>"
                              "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>User Name</b></font></td>"
                              "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Last Bind</b></font></td>"
                              "</tr>\n", r
                             );
-                    for (i=0; i < n->search_cache->size; ++i) {
-                        for (p = n->search_cache->nodes[i]; p != NULL; p = p->next) {
-
-                            (*n->search_cache->display)(r, n->search_cache, p->payload);
+                    if (n) {
+                        for (i=0; i < n->search_cache->size; ++i) {
+                            for (p = n->search_cache->nodes[i]; p != NULL; p = p->next) {
+    
+                                (*n->search_cache->display)(r, n->search_cache, p->payload);
+                            }
                         }
                     }
                     ap_rputs("</table>\n</p>\n", r);
                     break;
                 case 'c':
                     ap_rputs("<p>\n"
