              "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Ins/Rem</b></font></td>"
              "<td colspan='2'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Purges</b></font></td>"
              "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Avg Purge Time</b></font></td>"
              "</tr>\n", r
             );
 
-    ap_rputs(util_ald_cache_display(r->pool), r);
+    ap_rputs(util_ald_cache_display(r->pool, st), r);
 
     ap_rputs("</table>\n</p>\n", r);
 
     return OK;
 }
 
