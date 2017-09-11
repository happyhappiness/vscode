@@ -490,6 +490,51 @@ static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
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
+    if (strstr(s,"<redis>")) color = "green";
+    if (strstr(s,"<reply>")) color = "cyan";
+    if (strstr(s,"<error>")) color = "red";
+    if (strstr(s,"<value>")) color = "magenta";
+    if (isdigit(s[0])) {
+        char *p = s+1;
+        while(isdigit(*p)) p++;
+        if (*p == '*') color = "yellow"; /* Current line. */
+        else if (*p == '#') color = "bold"; /* Break point. */
+    }
+    return sdscatcolor(o,s,len,color);
+}
+
 static sds cliFormatReplyRaw(redisReply *r) {
     sds out = sdsempty(), tmp;
     size_t i;
@@ -504,7 +549,14 @@ static sds cliFormatReplyRaw(redisReply *r) {
         break;
     case REDIS_REPLY_STATUS:
     case REDIS_REPLY_STRING:
-        out = sdscatlen(out,r->str,r->len);
+        if (r->type == REDIS_REPLY_STATUS && config.eval_ldb) {
+            /* The Lua debugger replies with arrays of simple (status)
+             * strings. We colorize the output for more fun if this
+             * is a debugging session. */
+            out = sdsCatColorizedLdbReply(out,r->str,r->len);
+        } else {
+            out = sdscatlen(out,r->str,r->len);
+        }
         break;
     case REDIS_REPLY_INTEGER:
         out = sdscatprintf(out,"%lld",r->integer);