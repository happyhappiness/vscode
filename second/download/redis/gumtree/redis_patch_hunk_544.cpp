         fprintf(stderr,"Unknown reply type: %d\n", r->type);
         exit(1);
     }
     return out;
 }
 
+int isColorTerm(void) {
+    char *t = getenv("TERM");
+    return t != NULL && strstr(t,"xterm") != NULL;
+}
+
+/* Helpe  function for sdsCatColorizedLdbReply() appending colorize strings
+ * to an SDS string. */
+sds sdscatcolor(sds o, char *s, size_t len, char *color) {
+    if (!isColorTerm()) return sdscatlen(o,s,len);
+
+    int bold = strstr(color,"bold") != NULL;
+    int ccode = 37; /* Defaults to white. */
+    if (strstr(color,"red")) ccode = 31;
+    else if (strstr(color,"red")) ccode = 31;
+    else if (strstr(color,"green")) ccode = 32;
+    else if (strstr(color,"yellow")) ccode = 33;
+    else if (strstr(color,"blue")) ccode = 34;
+    else if (strstr(color,"magenta")) ccode = 35;
+    else if (strstr(color,"cyan")) ccode = 36;
+    else if (strstr(color,"white")) ccode = 37;
+
+    o = sdscatfmt(o,"\033[%i;%i;49m",bold,ccode);
+    o = sdscatlen(o,s,len);
+    o = sdscat(o,"\033[0m");
+    return o;
+}
+
+/* Colorize Lua debugger status replies according to the prefix they
+ * have. */
+sds sdsCatColorizedLdbReply(sds o, char *s, size_t len) {
+    char *color = "white";
+
+    if (strstr(s,"<debug>")) color = "bold";
+    if (strstr(s,"<redis>")) color = "green";
+    if (strstr(s,"<reply>")) color = "cyan";
+    if (strstr(s,"<error>")) color = "red";
+    if (strstr(s,"<hint>")) color = "bold";
+    if (strstr(s,"<value>") || strstr(s,"<retval>")) color = "magenta";
+    if (len > 4 && isdigit(s[3])) {
+        if (s[1] == '>') color = "yellow"; /* Current line. */
+        else if (s[2] == '#') color = "bold"; /* Break point. */
+    }
+    return sdscatcolor(o,s,len,color);
+}
+
 static sds cliFormatReplyRaw(redisReply *r) {
     sds out = sdsempty(), tmp;
     size_t i;
 
     switch (r->type) {
     case REDIS_REPLY_NIL:
