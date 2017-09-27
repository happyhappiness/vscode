              "Apache Server Information</h1>\n", r);
     if (!r->args || strcasecmp(r->args, "list")) {
         if (!r->args) {
             ap_rputs("<dl><dt><tt>Subpages:<br />", r);
             ap_rputs("<a href=\"?config\">Configuration Files</a>, "
                      "<a href=\"?server\">Server Settings</a>, "
-                     "<a href=\"?list\">Module List</a>,  "
-                     "<a href=\"?hooks\">Active Hooks</a>", r);
+                     "<a href=\"?list\">Module List</a>, "
+                     "<a href=\"?hooks\">Active Hooks</a>, "
+                     "<a href=\"?providers\">Available Providers</a>", r);
             ap_rputs("</tt></dt></dl><hr />", r);
 
             ap_rputs("<dl><dt><tt>Sections:<br />", r);
             ap_rputs("<a href=\"#modules\">Loaded Modules</a>, "
                      "<a href=\"#server\">Server Settings</a>, "
                      "<a href=\"#startup_hooks\">Startup Hooks</a>, "
                      "<a href=\"#request_hooks\">Request Hooks</a>, "
-                     "<a href=\"#other_hooks\">Other Hooks</a>", r);
+                     "<a href=\"#other_hooks\">Other Hooks</a>, "
+                     "<a href=\"#providers\">Providers</a>", r);
             ap_rputs("</tt></dt></dl><hr />", r);
 
             ap_rputs("<h2><a name=\"modules\">Loaded Modules</a></h2>"
                     "<dl><dt><tt>", r);
 
             modules = get_sorted_modules(r->pool);
