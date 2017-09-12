@@ -192,14 +192,14 @@ static unsigned long zipmapRequiredLength(unsigned int klen, unsigned int vlen)
     return l;
 }
 
-/* Return the total amonut used by a key (encoded length + payload) */
+/* Return the total amount used by a key (encoded length + payload) */
 static unsigned int zipmapRawKeyLength(unsigned char *p) {
     unsigned int l = zipmapDecodeLength(p);
     
     return zipmapEncodeLength(NULL,l) + l;
 }
 
-/* Return the total amonut used by a value
+/* Return the total amount used by a value
  * (encoded length + single byte free count + payload) */
 static unsigned int zipmapRawValueLength(unsigned char *p) {
     unsigned int l = zipmapDecodeLength(p);
@@ -303,7 +303,7 @@ void zipmapRepr(unsigned char *p) {
             p += zipmapEncodeLength(NULL,l);
             e = *p++;
             fwrite(p,l,1,stdout);
-            p += l;
+            p += l+e;
             if (e) {
                 printf("[");
                 while(e--) printf(".");
@@ -320,6 +320,7 @@ int main(void) {
     zm = zipmapNew();
     zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6);
     zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3);
+    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "!",1);
     zipmapRepr(zm);
     return 0;
 }