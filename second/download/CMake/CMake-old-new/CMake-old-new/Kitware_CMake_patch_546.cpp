@@ -1,14 +1,13 @@
 /* This source code was modified by Martin Hedenfalk <mhe@stacken.kth.se> for
- * use in Curl. His latest changes were done 2000-09-18.
+ * use in Curl. Martin's latest changes were done 2000-09-18.
  *
- * It has since been patched away like a madman by Daniel Stenberg
- * <daniel@haxx.se> to make it better applied to curl conditions, and to make
- * it not use globals, pollute name space and more. This source code awaits a
- * rewrite to work around the paragraph 2 in the BSD licenses as explained
- * below.
+ * It has since been patched away like a madman by Daniel Stenberg to make it
+ * better applied to curl conditions, and to make it not use globals, pollute
+ * name space and more.
  *
  * Copyright (c) 1995, 1996, 1997, 1998, 1999 Kungliga Tekniska H�gskolan
  * (Royal Institute of Technology, Stockholm, Sweden).
+ * Copyright (c) 2004 - 2007 Daniel Stenberg
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -36,15 +35,16 @@
  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
- * SUCH DAMAGE.  */
+ * SUCH DAMAGE.
+ *
+ * $Id$
+ */
 
 #include "setup.h"
 
 #ifndef CURL_DISABLE_FTP
 #ifdef HAVE_KRB4
 
-#include "security.h"
-#include "base64.h"
 #include <stdlib.h>
 #ifdef HAVE_NETDB_H
 #include <netdb.h>
@@ -57,10 +57,12 @@
 #include <unistd.h> /* for getpid() */
 #endif
 
+#include "urldata.h"
+#include "base64.h"
 #include "ftp.h"
 #include "sendf.h"
 #include "krb4.h"
-#include "curl_memory.h"
+#include "memory.h"
 
 #if defined(HAVE_INET_NTOA_R) && !defined(HAVE_INET_NTOA_R_DECL)
 #include "inet_ntoa_r.h"
@@ -199,7 +201,8 @@ krb4_auth(void *app_data, struct connectdata *conn)
 {
   int ret;
   char *p;
-  int len;
+  unsigned char *ptr;
+  size_t len;
   KTEXT_ST adat;
   MSG_DAT msg_data;
   int checksum;
@@ -220,7 +223,7 @@ krb4_auth(void *app_data, struct connectdata *conn)
   if(ret == KDC_PR_UNKNOWN)
     ret = mk_auth(d, &adat, "rcmd", host, checksum);
   if(ret) {
-    Curl_infof(data, "%s\n", krb_get_err_text(ret));
+    infof(data, "%s\n", krb_get_err_text(ret));
     return AUTH_CONTINUE;
   }
 
@@ -232,7 +235,7 @@ krb4_auth(void *app_data, struct connectdata *conn)
     if (krb_get_our_ip_for_realm(krb_realmofhost(host),
                                  &natAddr) != KSUCCESS
         && krb_get_our_ip_for_realm(NULL, &natAddr) != KSUCCESS)
-      Curl_infof(data, "Can't get address for realm %s\n",
+      infof(data, "Can't get address for realm %s\n",
                  krb_realmofhost(host));
     else {
       if (natAddr.s_addr != localaddr->sin_addr.s_addr) {
@@ -242,14 +245,14 @@ krb4_auth(void *app_data, struct connectdata *conn)
 #else
         char *ip = (char *)inet_ntoa(natAddr);
 #endif
-        Curl_infof(data, "Using NAT IP address (%s) for kerberos 4\n", ip);
+        infof(data, "Using NAT IP address (%s) for kerberos 4\n", ip);
         localaddr->sin_addr = natAddr;
       }
     }
   }
 #endif
 
-  if(Curl_base64_encode((char *)adat.dat, adat.length, &p) < 1) {
+  if(Curl_base64_encode(conn->data, (char *)adat.dat, adat.length, &p) < 1) {
     Curl_failf(data, "Out of memory base64-encoding");
     return AUTH_CONTINUE;
   }
@@ -275,11 +278,17 @@ krb4_auth(void *app_data, struct connectdata *conn)
     return AUTH_ERROR;
   }
   p += 5;
-  len = Curl_base64_decode(p, (char *)adat.dat);
-  if(len < 0) {
+  len = Curl_base64_decode(p, &ptr);
+  if(len > sizeof(adat.dat)-1) {
+    free(ptr);
+    len=0;
+  }
+  if(!len || !ptr) {
     Curl_failf(data, "Failed to decode base64 from server");
     return AUTH_ERROR;
   }
+  memcpy((char *)adat.dat, ptr, len);
+  free(ptr);
   adat.length = len;
   ret = krb_rd_safe(adat.dat, adat.length, &d->key,
                     (struct sockaddr_in *)hisctladdr,
@@ -317,10 +326,11 @@ CURLcode Curl_krb_kauth(struct connectdata *conn)
   char *name;
   char *p;
   char passwd[100];
-  int tmp;
+  size_t tmp;
   ssize_t nread;
   int save;
   CURLcode result;
+  unsigned char *ptr;
 
   save = Curl_set_command_prot(conn, prot_private);
 
@@ -346,12 +356,18 @@ CURLcode Curl_krb_kauth(struct connectdata *conn)
   }
 
   p += 2;
-  tmp = Curl_base64_decode(p, (char *)tkt.dat);
-  if(tmp < 0) {
+  tmp = Curl_base64_decode(p, &ptr);
+  if(tmp >= sizeof(tkt.dat)) {
+    free(ptr);
+    tmp=0;
+  }
+  if(!tmp || !ptr) {
     Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
     Curl_set_command_prot(conn, save);
     return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
+  memcpy((char *)tkt.dat, ptr, tmp);
+  free(ptr);
   tkt.length = tmp;
   tktcopy.length = tkt.length;
 
@@ -384,7 +400,8 @@ CURLcode Curl_krb_kauth(struct connectdata *conn)
   memset(key, 0, sizeof(key));
   memset(schedule, 0, sizeof(schedule));
   memset(passwd, 0, sizeof(passwd));
-  if(Curl_base64_encode((char *)tktcopy.dat, tktcopy.length, &p) < 1) {
+  if(Curl_base64_encode(conn->data, (char *)tktcopy.dat, tktcopy.length, &p)
+     < 1) {
     failf(conn->data, "Out of memory base64-encoding.");
     Curl_set_command_prot(conn, save);
     return CURLE_OUT_OF_MEMORY;