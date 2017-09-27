                                    really href's */
     }
     if (!strcasecmp(menu, "formatted")) {
         ap_rvputs(r, "<pre>(Default) <a href=\"", href, "\">", text,
                "</a></pre>\n", NULL);
     }
-    if (!strcasecmp(menu, "semiformatted")) {
+    else if (!strcasecmp(menu, "semiformatted")) {
         ap_rvputs(r, "<pre>(Default) <a href=\"", href, "\">", text,
                "</a></pre>\n", NULL);
     }
-    if (!strcasecmp(menu, "unformatted")) {
+    else if (!strcasecmp(menu, "unformatted")) {
         ap_rvputs(r, "<a href=\"", href, "\">", text, "</a>", NULL);
     }
     return;
 }
 
 static void menu_directive(request_rec *r, char *menu, char *href, char *text)
