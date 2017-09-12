@@ -26,6 +26,12 @@
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
+ *
+ * History:
+ *
+ * - 22 March 2011: History section created on top of sds.c
+ * - 22 March 2011: Fixed a problem with "\xab" escapes convertion in
+ *                  function sdssplitargs().
  */
 
 #define SDS_ABORT_ON_OOM
@@ -45,18 +51,20 @@ static void sdsOomAbort(void) {
 sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
 
-    sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
+    if (init) {
+        sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
+    } else {
+        sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
+    }
 #ifdef SDS_ABORT_ON_OOM
     if (sh == NULL) sdsOomAbort();
 #else
     if (sh == NULL) return NULL;
 #endif
     sh->len = initlen;
     sh->free = 0;
-    if (initlen) {
-        if (init) memcpy(sh->buf, init, initlen);
-        else memset(sh->buf,0,initlen);
-    }
+    if (initlen && init)
+        memcpy(sh->buf, init, initlen);
     sh->buf[initlen] = '\0';
     return (char*)sh->buf;
 }
@@ -399,11 +407,11 @@ sds sdscatrepr(sds s, char *p, size_t len) {
         case '"':
             s = sdscatprintf(s,"\\%c",*p);
             break;
-        case '\n': s = sdscatlen(s,"\\n",1); break;
-        case '\r': s = sdscatlen(s,"\\r",1); break;
-        case '\t': s = sdscatlen(s,"\\t",1); break;
-        case '\a': s = sdscatlen(s,"\\a",1); break;
-        case '\b': s = sdscatlen(s,"\\b",1); break;
+        case '\n': s = sdscatlen(s,"\\n",2); break;
+        case '\r': s = sdscatlen(s,"\\r",2); break;
+        case '\t': s = sdscatlen(s,"\\t",2); break;
+        case '\a': s = sdscatlen(s,"\\a",2); break;
+        case '\b': s = sdscatlen(s,"\\b",2); break;
         default:
             if (isprint(*p))
                 s = sdscatprintf(s,"%c",*p);
@@ -416,6 +424,37 @@ sds sdscatrepr(sds s, char *p, size_t len) {
     return sdscatlen(s,"\"",1);
 }
 
+/* Helper function for sdssplitargs() that returns non zero if 'c'
+ * is a valid hex digit. */
+int is_hex_digit(char c) {
+    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
+           (c >= 'A' && c <= 'F');
+}
+
+/* Helper function for sdssplitargs() that converts an hex digit into an
+ * integer from 0 to 15 */
+int hex_digit_to_int(char c) {
+    switch(c) {
+    case '0': return 0;
+    case '1': return 1;
+    case '2': return 2;
+    case '3': return 3;
+    case '4': return 4;
+    case '5': return 5;
+    case '6': return 6;
+    case '7': return 7;
+    case '8': return 8;
+    case '9': return 9;
+    case 'a': case 'A': return 10;
+    case 'b': case 'B': return 11;
+    case 'c': case 'C': return 12;
+    case 'd': case 'D': return 13;
+    case 'e': case 'E': return 14;
+    case 'f': case 'F': return 15;
+    default: return 0;
+    }
+}
+
 /* Split a line into arguments, where every argument can be in the
  * following programming-language REPL-alike form:
  *
@@ -445,7 +484,17 @@ sds *sdssplitargs(char *line, int *argc) {
             if (current == NULL) current = sdsempty();
             while(!done) {
                 if (inq) {
-                    if (*p == '\\' && *(p+1)) {
+                    if (*p == '\\' && *(p+1) == 'x' &&
+                                             is_hex_digit(*(p+2)) &&
+                                             is_hex_digit(*(p+3)))
+                    {
+                        unsigned char byte;
+
+                        byte = (hex_digit_to_int(*(p+2))*16)+
+                                hex_digit_to_int(*(p+3));
+                        current = sdscatlen(current,(char*)&byte,1);
+                        p += 3;
+                    } else if (*p == '\\' && *(p+1)) {
                         char c;
 
                         p++;