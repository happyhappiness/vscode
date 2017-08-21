@@ -40,6 +40,9 @@
 #include "curl_memory.h"
 #include "memdebug.h"
 
+/* For overflow checks. */
+#define CURL_SIZE_T_MAX         ((size_t)-1)
+
 
 /* ASN.1 OIDs. */
 static const char       cnOID[] = "2.5.4.3";    /* Common name. */
@@ -105,8 +108,8 @@ static const curl_OID   OIDtable[] = {
  */
 
 
-const char * Curl_getASN1Element(curl_asn1Element * elem,
-                                 const char * beg, const char * end)
+const char *Curl_getASN1Element(curl_asn1Element *elem,
+                                const char *beg, const char *end)
 {
   unsigned char b;
   unsigned long len;
@@ -116,8 +119,8 @@ const char * Curl_getASN1Element(curl_asn1Element * elem,
      ending at `end'.
      Returns a pointer in source string after the parsed element, or NULL
      if an error occurs. */
-
-  if(beg >= end || !*beg)
+  if(!beg || !end || beg >= end || !*beg ||
+     (size_t)(end - beg) > CURL_ASN1_MAX)
     return (const char *) NULL;
 
   /* Process header byte. */
@@ -152,7 +155,7 @@ const char * Curl_getASN1Element(curl_asn1Element * elem,
     elem->end = beg;
     return beg + 1;
   }
-  else if(beg + b > end)
+  else if((unsigned)b > (size_t)(end - beg))
     return (const char *) NULL; /* Does not fit in source. */
   else {
     /* Get long length. */
@@ -163,16 +166,16 @@ const char * Curl_getASN1Element(curl_asn1Element * elem,
       len = (len << 8) | (unsigned char) *beg++;
     } while(--b);
   }
-  if((unsigned long) (end - beg) < len)
+  if(len > (size_t)(end - beg))
     return (const char *) NULL;  /* Element data does not fit in source. */
   elem->beg = beg;
   elem->end = beg + len;
   return elem->end;
 }
 
-static const curl_OID * searchOID(const char * oid)
+static const curl_OID * searchOID(const char *oid)
 {
-  const curl_OID * op;
+  const curl_OID *op;
 
   /* Search the null terminated OID or OID identifier in local table.
      Return the table entry pointer or NULL if not found. */
@@ -184,7 +187,7 @@ static const curl_OID * searchOID(const char * oid)
   return (const curl_OID *) NULL;
 }
 
-static const char * bool2str(const char * beg, const char * end)
+static const char *bool2str(const char *beg, const char *end)
 {
   /* Convert an ASN.1 Boolean value into its string representation.
      Return the dynamically allocated string, or NULL if source is not an
@@ -195,22 +198,24 @@ static const char * bool2str(const char * beg, const char * end)
   return strdup(*beg? "TRUE": "FALSE");
 }
 
-static const char * octet2str(const char * beg, const char * end)
+static const char *octet2str(const char *beg, const char *end)
 {
   size_t n = end - beg;
-  char * buf;
+  char *buf = NULL;
 
   /* Convert an ASN.1 octet string to a printable string.
      Return the dynamically allocated string, or NULL if an error occurs. */
 
-  buf = malloc(3 * n + 1);
-  if(buf)
-    for(n = 0; beg < end; n += 3)
-      snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++);
+  if(n <= (CURL_SIZE_T_MAX - 1) / 3) {
+    buf = malloc(3 * n + 1);
+    if(buf)
+      for(n = 0; beg < end; n += 3)
+        snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++);
+  }
   return buf;
 }
 
-static const char * bit2str(const char * beg, const char * end)
+static const char *bit2str(const char *beg, const char *end)
 {
   /* Convert an ASN.1 bit string to a printable string.
      Return the dynamically allocated string, or NULL if an error occurs. */
@@ -220,7 +225,7 @@ static const char * bit2str(const char * beg, const char * end)
   return octet2str(beg, end);
 }
 
-static const char * int2str(const char * beg, const char * end)
+static const char *int2str(const char *beg, const char *end)
 {
   long val = 0;
   size_t n = end - beg;
@@ -246,14 +251,14 @@ static const char * int2str(const char * beg, const char * end)
 }
 
 static ssize_t
-utf8asn1str(char * * to, int type, const char * from, const char * end)
+utf8asn1str(char **to, int type, const char *from, const char *end)
 {
   size_t inlength = end - from;
   int size = 1;
   size_t outlength;
   int charsize;
   unsigned int wc;
-  char * buf;
+  char *buf;
 
   /* Perform a lazy conversion from an ASN.1 typed string to UTF8. Allocate the
      destination buffer dynamically. The allocation size will normally be too
@@ -262,7 +267,7 @@ utf8asn1str(char * * to, int type, const char * from, const char * end)
      string length. */
 
   *to = (char *) NULL;
-  switch (type) {
+  switch(type) {
   case CURL_ASN1_BMP_STRING:
     size = 2;
     break;
@@ -282,6 +287,8 @@ utf8asn1str(char * * to, int type, const char * from, const char * end)
 
   if(inlength % size)
     return -1;  /* Length inconsistent with character size. */
+  if(inlength / size > (CURL_SIZE_T_MAX - 1) / 4)
+    return -1;  /* Too big. */
   buf = malloc(4 * (inlength / size) + 1);
   if(!buf)
     return -1;  /* Not enough memory. */
@@ -295,7 +302,7 @@ utf8asn1str(char * * to, int type, const char * from, const char * end)
   else {
     for(outlength = 0; from < end;) {
       wc = 0;
-      switch (size) {
+      switch(size) {
       case 4:
         wc = (wc << 8) | *(const unsigned char *) from++;
         wc = (wc << 8) | *(const unsigned char *) from++;
@@ -335,9 +342,9 @@ utf8asn1str(char * * to, int type, const char * from, const char * end)
   return outlength;
 }
 
-static const char * string2str(int type, const char * beg, const char * end)
+static const char *string2str(int type, const char *beg, const char *end)
 {
-  char * buf;
+  char *buf;
 
   /* Convert an ASN.1 String into its UTF-8 string representation.
      Return the dynamically allocated string, or NULL if an error occurs. */
@@ -347,7 +354,7 @@ static const char * string2str(int type, const char * beg, const char * end)
   return buf;
 }
 
-static int encodeUint(char * buf, int n, unsigned int x)
+static int encodeUint(char *buf, int n, unsigned int x)
 {
   int i = 0;
   unsigned int y = x / 10;
@@ -367,7 +374,7 @@ static int encodeUint(char * buf, int n, unsigned int x)
   return i;
 }
 
-static int encodeOID(char * buf, int n, const char * beg, const char * end)
+static int encodeOID(char *buf, int n, const char *beg, const char *end)
 {
   int i = 0;
   unsigned int x;
@@ -406,9 +413,9 @@ static int encodeOID(char * buf, int n, const char * beg, const char * end)
   return i;
 }
 
-static const char * OID2str(const char * beg, const char * end, bool symbolic)
+static const char *OID2str(const char *beg, const char *end, bool symbolic)
 {
-  char * buf = (char *) NULL;
+  char *buf = (char *) NULL;
   const curl_OID * op;
   int n;
 
@@ -436,14 +443,14 @@ static const char * OID2str(const char * beg, const char * end, bool symbolic)
   return buf;
 }
 
-static const char * GTime2str(const char * beg, const char * end)
+static const char *GTime2str(const char *beg, const char *end)
 {
-  const char * tzp;
-  const char * fracp;
+  const char *tzp;
+  const char *fracp;
   char sec1, sec2;
   size_t fracl;
   size_t tzl;
-  const char * sep = "";
+  const char *sep = "";
 
   /* Convert an ASN.1 Generalized time to a printable string.
      Return the dynamically allocated string, or NULL if an error occurs. */
@@ -453,7 +460,7 @@ static const char * GTime2str(const char * beg, const char * end)
 
   /* Get seconds digits. */
   sec1 = '0';
-  switch (fracp - beg - 12) {
+  switch(fracp - beg - 12) {
   case 0:
     sec2 = '0';
     break;
@@ -499,11 +506,11 @@ static const char * GTime2str(const char * beg, const char * end)
                        sep, tzl, tzp);
 }
 
-static const char * UTime2str(const char * beg, const char * end)
+static const char *UTime2str(const char *beg, const char *end)
 {
-  const char * tzp;
+  const char *tzp;
   size_t tzl;
-  const char * sec;
+  const char *sec;
 
   /* Convert an ASN.1 UTC time to a printable string.
      Return the dynamically allocated string, or NULL if an error occurs. */
@@ -512,7 +519,7 @@ static const char * UTime2str(const char * beg, const char * end)
     ;
   /* Get the seconds. */
   sec = beg + 10;
-  switch (tzp - sec) {
+  switch(tzp - sec) {
   case 0:
     sec = "00";
   case 2:
@@ -538,7 +545,7 @@ static const char * UTime2str(const char * beg, const char * end)
                        tzl, tzp);
 }
 
-const char * Curl_ASN1tostr(curl_asn1Element * elem, int type)
+const char *Curl_ASN1tostr(curl_asn1Element *elem, int type)
 {
   /* Convert an ASN.1 element to a printable string.
      Return the dynamically allocated string, or NULL if an error occurs. */
@@ -549,7 +556,7 @@ const char * Curl_ASN1tostr(curl_asn1Element * elem, int type)
   if(!type)
     type = elem->tag;   /* Type not forced: use element tag as type. */
 
-  switch (type) {
+  switch(type) {
   case CURL_ASN1_BOOLEAN:
     return bool2str(elem->beg, elem->end);
   case CURL_ASN1_INTEGER:
@@ -581,17 +588,17 @@ const char * Curl_ASN1tostr(curl_asn1Element * elem, int type)
   return (const char *) NULL;   /* Unsupported. */
 }
 
-static ssize_t encodeDN(char * buf, size_t n, curl_asn1Element * dn)
+static ssize_t encodeDN(char *buf, size_t n, curl_asn1Element *dn)
 {
   curl_asn1Element rdn;
   curl_asn1Element atv;
   curl_asn1Element oid;
   curl_asn1Element value;
   size_t l = 0;
-  const char * p1;
-  const char * p2;
-  const char * p3;
-  const char * str;
+  const char *p1;
+  const char *p2;
+  const char *p3;
+  const char *str;
 
   /* ASCII encode distinguished name at `dn' into the `n'-byte buffer at `buf'.
      Return the total string length, even if larger than `n'. */
@@ -647,9 +654,9 @@ static ssize_t encodeDN(char * buf, size_t n, curl_asn1Element * dn)
   return l;
 }
 
-const char * Curl_DNtostr(curl_asn1Element * dn)
+const char *Curl_DNtostr(curl_asn1Element *dn)
 {
-  char * buf = (char *) NULL;
+  char *buf = (char *) NULL;
   ssize_t n = encodeDN(buf, 0, dn);
 
   /* Convert an ASN.1 distinguished name into a printable string.
@@ -669,12 +676,12 @@ const char * Curl_DNtostr(curl_asn1Element * dn)
  * X509 parser.
  */
 
-void Curl_parseX509(curl_X509certificate * cert,
-                    const char * beg, const char * end)
+int Curl_parseX509(curl_X509certificate *cert,
+                   const char *beg, const char *end)
 {
   curl_asn1Element elem;
   curl_asn1Element tbsCertificate;
-  const char * ccp;
+  const char *ccp;
   static const char defaultVersion = 0;  /* v1. */
 
   /* ASN.1 parse an X509 certificate into structure subfields.
@@ -686,7 +693,8 @@ void Curl_parseX509(curl_X509certificate * cert,
   cert->certificate.end = end;
 
   /* Get the sequence content. */
-  Curl_getASN1Element(&elem, beg, end);
+  if(!Curl_getASN1Element(&elem, beg, end))
+    return -1;  /* Invalid bounds/size. */
   beg = elem.beg;
   end = elem.end;
 
@@ -749,9 +757,10 @@ void Curl_parseX509(curl_X509certificate * cert,
   }
   if(elem.tag == 3)
     Curl_getASN1Element(&cert->extensions, elem.beg, elem.end);
+  return 0;
 }
 
-static size_t copySubstring(char * to, const char * from)
+static size_t copySubstring(char *to, const char *from)
 {
   size_t i;
 
@@ -768,8 +777,8 @@ static size_t copySubstring(char * to, const char * from)
   return i;
 }
 
-static const char * dumpAlgo(curl_asn1Element * param,
-                             const char * beg, const char * end)
+static const char *dumpAlgo(curl_asn1Element *param,
+                            const char *beg, const char *end)
 {
   curl_asn1Element oid;
 
@@ -784,10 +793,10 @@ static const char * dumpAlgo(curl_asn1Element * param,
   return OID2str(oid.beg, oid.end, TRUE);
 }
 
-static void do_pubkey_field(struct Curl_easy * data, int certnum,
-                            const char * label, curl_asn1Element * elem)
+static void do_pubkey_field(struct Curl_easy *data, int certnum,
+                            const char *label, curl_asn1Element *elem)
 {
-  const char * output;
+  const char *output;
 
   /* Generate a certificate information record for the public key. */
 
@@ -801,14 +810,14 @@ static void do_pubkey_field(struct Curl_easy * data, int certnum,
   }
 }
 
-static void do_pubkey(struct Curl_easy * data, int certnum,
-                      const char * algo, curl_asn1Element * param,
-                      curl_asn1Element * pubkey)
+static void do_pubkey(struct Curl_easy *data, int certnum,
+                      const char *algo, curl_asn1Element *param,
+                      curl_asn1Element *pubkey)
 {
   curl_asn1Element elem;
   curl_asn1Element pk;
-  const char * p;
-  const char * q;
+  const char *p;
+  const char *q;
   unsigned long len;
   unsigned int i;
 
@@ -865,18 +874,18 @@ static void do_pubkey(struct Curl_easy * data, int certnum,
 #endif
 }
 
-CURLcode Curl_extract_certinfo(struct connectdata * conn,
+CURLcode Curl_extract_certinfo(struct connectdata *conn,
                                int certnum,
-                               const char * beg,
-                               const char * end)
+                               const char *beg,
+                               const char *end)
 {
   curl_X509certificate cert;
-  struct Curl_easy * data = conn->data;
+  struct Curl_easy *data = conn->data;
   curl_asn1Element param;
-  const char * ccp;
-  char * cp1;
+  const char *ccp;
+  char *cp1;
   size_t cl1;
-  char * cp2;
+  char *cp2;
   CURLcode result;
   unsigned long version;
   size_t i;
@@ -889,7 +898,8 @@ CURLcode Curl_extract_certinfo(struct connectdata * conn,
   /* Prepare the certificate information for curl_easy_getinfo(). */
 
   /* Extract the certificate ASN.1 elements. */
-  Curl_parseX509(&cert, beg, end);
+  if(Curl_parseX509(&cert, beg, end))
+    return CURLE_OUT_OF_MEMORY;
 
   /* Subject. */
   ccp = Curl_DNtostr(&cert.subject);
@@ -1029,12 +1039,12 @@ CURLcode Curl_extract_certinfo(struct connectdata * conn,
 
 #if defined(USE_GSKIT)
 
-static const char * checkOID(const char * beg, const char * end,
-                             const char * oid)
+static const char *checkOID(const char *beg, const char *end,
+                            const char *oid)
 {
   curl_asn1Element e;
-  const char * ccp;
-  const char * p;
+  const char *ccp;
+  const char *p;
   bool matched;
 
   /* Check if first ASN.1 element at `beg' is the given OID.
@@ -1053,21 +1063,26 @@ static const char * checkOID(const char * beg, const char * end,
   return matched? ccp: (const char *) NULL;
 }
 
-CURLcode Curl_verifyhost(struct connectdata * conn,
-                         const char * beg, const char * end)
+CURLcode Curl_verifyhost(struct connectdata *conn,
+                         const char *beg, const char *end)
 {
-  struct Curl_easy * data = conn->data;
+  struct Curl_easy *data = conn->data;
   curl_X509certificate cert;
   curl_asn1Element dn;
   curl_asn1Element elem;
   curl_asn1Element ext;
   curl_asn1Element name;
-  const char * p;
-  const char * q;
-  char * dnsname;
+  const char *p;
+  const char *q;
+  char *dnsname;
   int matched = -1;
   size_t addrlen = (size_t) -1;
   ssize_t len;
+  const char * const hostname = SSL_IS_PROXY()? conn->http_proxy.host.name:
+                                                conn->host.name;
+  const char * const dispname = SSL_IS_PROXY()?
+                                  conn->http_proxy.host.dispname:
+                                  conn->host.dispname;
 #ifdef ENABLE_IPV6
   struct in6_addr addr;
 #else
@@ -1077,20 +1092,19 @@ CURLcode Curl_verifyhost(struct connectdata * conn,
   /* Verify that connection server matches info in X509 certificate at
      `beg'..`end'. */
 
-  if(!data->set.ssl.verifyhost)
+  if(!SSL_CONN_CONFIG(verifyhost))
     return CURLE_OK;
 
-  if(!beg)
+  if(Curl_parseX509(&cert, beg, end))
     return CURLE_PEER_FAILED_VERIFICATION;
-  Curl_parseX509(&cert, beg, end);
 
   /* Get the server IP address. */
 #ifdef ENABLE_IPV6
-  if(conn->bits.ipv6_ip && Curl_inet_pton(AF_INET6, conn->host.name, &addr))
+  if(conn->bits.ipv6_ip && Curl_inet_pton(AF_INET6, hostname, &addr))
     addrlen = sizeof(struct in6_addr);
   else
 #endif
-  if(Curl_inet_pton(AF_INET, conn->host.name, &addr))
+  if(Curl_inet_pton(AF_INET, hostname, &addr))
     addrlen = sizeof(struct in_addr);
 
   /* Process extensions. */
@@ -1108,12 +1122,12 @@ CURLcode Curl_verifyhost(struct connectdata * conn,
       /* Check all GeneralNames. */
       for(q = elem.beg; matched != 1 && q < elem.end;) {
         q = Curl_getASN1Element(&name, q, elem.end);
-        switch (name.tag) {
+        switch(name.tag) {
         case 2: /* DNS name. */
           len = utf8asn1str(&dnsname, CURL_ASN1_IA5_STRING,
                             name.beg, name.end);
           if(len > 0 && (size_t)len == strlen(dnsname))
-            matched = Curl_cert_hostcheck(dnsname, conn->host.name);
+            matched = Curl_cert_hostcheck(dnsname, hostname);
           else
             matched = 0;
           free(dnsname);
@@ -1128,15 +1142,15 @@ CURLcode Curl_verifyhost(struct connectdata * conn,
     }
   }
 
-  switch (matched) {
+  switch(matched) {
   case 1:
     /* an alternative name matched the server hostname */
-    infof(data, "\t subjectAltName: %s matched\n", conn->host.dispname);
+    infof(data, "\t subjectAltName: %s matched\n", dispname);
     return CURLE_OK;
   case 0:
     /* an alternative name field existed, but didn't match and then
        we MUST fail */
-    infof(data, "\t subjectAltName does not match %s\n", conn->host.dispname);
+    infof(data, "\t subjectAltName does not match %s\n", dispname);
     return CURLE_PEER_FAILED_VERIFICATION;
   }
 
@@ -1168,14 +1182,14 @@ CURLcode Curl_verifyhost(struct connectdata * conn,
     }
     if(strlen(dnsname) != (size_t) len)         /* Nul byte in string ? */
       failf(data, "SSL: illegal cert name field");
-    else if(Curl_cert_hostcheck((const char *) dnsname, conn->host.name)) {
+    else if(Curl_cert_hostcheck((const char *) dnsname, hostname)) {
       infof(data, "\t common name: %s (matched)\n", dnsname);
       free(dnsname);
       return CURLE_OK;
     }
     else
       failf(data, "SSL: certificate subject name '%s' does not match "
-            "target host name '%s'", dnsname, conn->host.dispname);
+            "target host name '%s'", dnsname, dispname);
     free(dnsname);
   }
 