     val = (val << 8) | *(const unsigned char *) beg++;
   while(beg < end);
   return curl_maprintf("%s%lx", (val < 0 || val >= 10)? "0x": "", val);
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
      large: this is to avoid buffer overflows.
      Terminate the string with a nul byte and return the converted
      string length. */
 
   *to = (char *) NULL;
-  switch (type) {
+  switch(type) {
   case CURL_ASN1_BMP_STRING:
     size = 2;
     break;
   case CURL_ASN1_UNIVERSAL_STRING:
     size = 4;
     break;
