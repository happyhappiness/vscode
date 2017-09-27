                  "\"<b><code>K</code></b>\" Keepalive (read), \n"
                  "\"<b><code>D</code></b>\" DNS Lookup,<br />\n"
                  "\"<b><code>C</code></b>\" Closing connection, \n"
                  "\"<b><code>L</code></b>\" Logging, \n"
                  "\"<b><code>G</code></b>\" Gracefully finishing,<br /> \n"
                  "\"<b><code>I</code></b>\" Idle cleanup of worker, \n"
-                 "\"<b><code>.</code></b>\" Open slot with no current process,<br />\n"
+                 "\"<b><code>.</code></b>\" Open slot with no current process<br />\n"
                  "<p />\n", r);
         if (!ap_extended_status) {
             int j;
             int k = 0;
             ap_rputs("PID Key: <br />\n"
                      "<pre>\n", r);
