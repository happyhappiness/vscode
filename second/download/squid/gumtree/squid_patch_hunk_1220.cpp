     p = xstrtok(&x, '\t');
 
     a_url = xstrdup(menu_url(req, a));
 
     /* no reason to give a url for a disabled action */
     if (!strcmp(p, "disabled"))
-        out.Printf("<LI type=\"circle\">%s (disabled)<A HREF=\"%s\">.</A>\n", d, a_url);
+        out.appendf("<LI type=\"circle\">%s (disabled)<A HREF=\"%s\">.</A>\n", d, a_url);
     else
         /* disable a hidden action (requires a password, but password is not in squid.conf) */
         if (!strcmp(p, "hidden"))
-            out.Printf("<LI type=\"circle\">%s (hidden)<A HREF=\"%s\">.</A>\n", d, a_url);
+            out.appendf("<LI type=\"circle\">%s (hidden)<A HREF=\"%s\">.</A>\n", d, a_url);
         else
             /* disable link if authentication is required and we have no password */
             if (!strcmp(p, "protected") && !req->passwd)
-                out.Printf("<LI type=\"circle\">%s (requires <a href=\"%s\">authentication</a>)<A HREF=\"%s\">.</A>\n",
-                           d, menu_url(req, "authenticate"), a_url);
+                out.appendf("<LI type=\"circle\">%s (requires <a href=\"%s\">authentication</a>)<A HREF=\"%s\">.</A>\n",
+                            d, menu_url(req, "authenticate"), a_url);
             else
                 /* highlight protected but probably available entries */
                 if (!strcmp(p, "protected"))
-                    out.Printf("<LI type=\"square\"><A HREF=\"%s\"><font color=\"#FF0000\">%s</font></A>\n",
-                               a_url, d);
+                    out.appendf("<LI type=\"square\"><A HREF=\"%s\"><font color=\"#FF0000\">%s</font></A>\n",
+                                a_url, d);
 
     /* public entry or unknown type of protection */
                 else
-                    out.Printf("<LI type=\"disk\"><A HREF=\"%s\">%s</A>\n", a_url, d);
+                    out.appendf("<LI type=\"disk\"><A HREF=\"%s\">%s</A>\n", a_url, d);
 
     xfree(a_url);
 
     xfree(buf_copy);
 }
 
