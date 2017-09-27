         ap_rvputs(r, "<pre>(Default) <a href=\"", ehref, "\">", etext,
                "</a></pre>\n", NULL);
     }
     else if (!strcasecmp(menu, "unformatted")) {
         ap_rvputs(r, "<a href=\"", ehref, "\">", etext, "</a>", NULL);
     }
-    return;
 }
 
 static void menu_directive(request_rec *r, const char *menu, const char *href, const char *text)
 {
     char *ehref, *etext;
     if (!strcasecmp(href, "error") || !strcasecmp(href, "nocontent")) {
