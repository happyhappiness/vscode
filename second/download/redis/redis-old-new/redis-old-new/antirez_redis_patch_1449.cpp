@@ -26,16 +26,8 @@
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
- *
- * History:
- *
- * - 22 March 2011: History section created on top of sds.c
- * - 22 March 2011: Fixed a problem with "\xab" escapes convertion in
- *                  function sdssplitargs().
  */
 
-#define SDS_ABORT_ON_OOM
-
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -44,11 +36,6 @@
 #include "sds.h"
 #include "zmalloc.h"
 
-static void sdsOomAbort(void) {
-    fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
-    abort();
-}
-
 sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
 
@@ -57,11 +44,7 @@ sds sdsnewlen(const void *init, size_t initlen) {
     } else {
         sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
     }
-#ifdef SDS_ABORT_ON_OOM
-    if (sh == NULL) sdsOomAbort();
-#else
     if (sh == NULL) return NULL;
-#endif
     sh->len = initlen;
     sh->free = 0;
     if (initlen && init)
@@ -122,11 +105,7 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
     else
         newlen += SDS_MAX_PREALLOC;
     newsh = zrealloc(sh, sizeof(struct sdshdr)+newlen+1);
-#ifdef SDS_ABORT_ON_OOM
-    if (newsh == NULL) sdsOomAbort();
-#else
     if (newsh == NULL) return NULL;
-#endif
 
     newsh->free = newlen - len;
     return newsh->buf;
@@ -232,11 +211,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
 
     while(1) {
         buf = zmalloc(buflen);
-#ifdef SDS_ABORT_ON_OOM
-        if (buf == NULL) sdsOomAbort();
-#else
         if (buf == NULL) return NULL;
-#endif
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
@@ -356,11 +331,7 @@ sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count) {
     if (seplen < 1 || len < 0) return NULL;
 
     tokens = zmalloc(sizeof(sds)*slots);
-#ifdef SDS_ABORT_ON_OOM
-    if (tokens == NULL) sdsOomAbort();
-#else
     if (tokens == NULL) return NULL;
-#endif
 
     if (len == 0) {
         *count = 0;
@@ -373,44 +344,25 @@ sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count) {
 
             slots *= 2;
             newtokens = zrealloc(tokens,sizeof(sds)*slots);
-            if (newtokens == NULL) {
-#ifdef SDS_ABORT_ON_OOM
-                sdsOomAbort();
-#else
-                goto cleanup;
-#endif
-            }
+            if (newtokens == NULL) goto cleanup;
             tokens = newtokens;
         }
         /* search the separator */
         if ((seplen == 1 && *(s+j) == sep[0]) || (memcmp(s+j,sep,seplen) == 0)) {
             tokens[elements] = sdsnewlen(s+start,j-start);
-            if (tokens[elements] == NULL) {
-#ifdef SDS_ABORT_ON_OOM
-                sdsOomAbort();
-#else
-                goto cleanup;
-#endif
-            }
+            if (tokens[elements] == NULL) goto cleanup;
             elements++;
             start = j+seplen;
             j = j+seplen-1; /* skip the separator */
         }
     }
     /* Add the final element. We are sure there is room in the tokens array. */
     tokens[elements] = sdsnewlen(s+start,len-start);
-    if (tokens[elements] == NULL) {
-#ifdef SDS_ABORT_ON_OOM
-                sdsOomAbort();
-#else
-                goto cleanup;
-#endif
-    }
+    if (tokens[elements] == NULL) goto cleanup;
     elements++;
     *count = elements;
     return tokens;
 
-#ifndef SDS_ABORT_ON_OOM
 cleanup:
     {
         int i;
@@ -419,7 +371,6 @@ sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count) {
         *count = 0;
         return NULL;
     }
-#endif
 }
 
 void sdsfreesplitres(sds *tokens, int count) {