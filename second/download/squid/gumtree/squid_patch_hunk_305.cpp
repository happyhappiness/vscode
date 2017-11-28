     printf("size=\"30\" VALUE=\"\"></TD></TR>\n");
 
     printf("</TABLE><BR CLEAR=\"all\">\n");
 
     printf("<INPUT TYPE=\"submit\" VALUE=\"Continue...\">\n");
 
-    printf("</FORM>\n");
+    printf("</FORM></div>\n");
+
+    printf("<script type=\"text/javascript\">\n");
+    printf("var s = document.getElementById(\"server\");\n");
+    printf("for (var i = 0; i < s.childElementCount; i++) {\n");
+    printf(" TS(s.children[i].value, '');\n");
+    printf(" TS(s.children[i].value, 's');\n");
+    printf("}</script>\n");
 
     print_trailer();
 }
 
 static void
 error_html(const char *msg)
