   }
 
   if(c) {
     char *format_ptr;
 
     fputs("# Netscape HTTP Cookie File\n"
-          "# http://www.netscape.com/newsref/std/cookie_spec.html\n"
+          "# http://curlm.haxx.se/rfc/cookie_spec.html\n"
           "# This file was generated by libcurl! Edit at your own risk.\n\n",
           out);
     co = c->cookies;
 
     while(co) {
       format_ptr = get_netscape_format(co);
