     int max_daemons, forked, threaded;
 
     ap_rputs("<h2><a name=\"server\">Server Settings</a></h2>", r);
     ap_rprintf(r,
                "<dl><dt><strong>Server Version:</strong> "
                "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
-               ap_get_server_version());
+               ap_get_server_description());
     ap_rprintf(r,
                "<dt><strong>Server Built:</strong> "
                "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
                ap_get_server_built());
     ap_rprintf(r,
                "<dt><strong>Module Magic Number:</strong> "
