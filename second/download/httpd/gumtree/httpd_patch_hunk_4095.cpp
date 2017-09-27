         ap_rvputs(r, "<pre>          <a href=\"", ehref, "\">", etext,
                "</a></pre>\n", NULL);
     }
     else if (!strcasecmp(menu, "unformatted")) {
         ap_rvputs(r, "<a href=\"", ehref, "\">", etext, "</a>", NULL);
     }
-    return;
 }
 
 static void menu_footer(request_rec *r)
 {
     ap_rputs("\n\n</body>\n</html>\n", r);         /* finish the menu */
 }
