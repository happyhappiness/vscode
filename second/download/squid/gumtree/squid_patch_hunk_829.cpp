 #if !defined(IN6_ARE_ADDR_EQUAL) && _SQUID_WINDOWS_
 #define IN6_ARE_ADDR_EQUAL IN6_ADDR_EQUAL
 #endif
 
 /* Debugging only. Dump the address content when a fatal assert is encountered. */
 #define IASSERT(a,b)  \
-	if(!(b)){	printf("assert \"%s\" at line %d\n", a, __LINE__); \
-		printf("Ip::Address invalid? with isIPv4()=%c, isIPv6()=%c\n",(isIPv4()?'T':'F'),(isIPv6()?'T':'F')); \
-		printf("ADDRESS:"); \
-		for(unsigned int i = 0; i < sizeof(mSocketAddr_.sin6_addr); ++i) { \
-			printf(" %x", mSocketAddr_.sin6_addr.s6_addr[i]); \
-		} printf("\n"); assert(b); \
-	}
+    if(!(b)){   printf("assert \"%s\" at line %d\n", a, __LINE__); \
+        printf("Ip::Address invalid? with isIPv4()=%c, isIPv6()=%c\n",(isIPv4()?'T':'F'),(isIPv6()?'T':'F')); \
+        printf("ADDRESS:"); \
+        for(unsigned int i = 0; i < sizeof(mSocketAddr_.sin6_addr); ++i) { \
+            printf(" %x", mSocketAddr_.sin6_addr.s6_addr[i]); \
+        } printf("\n"); assert(b); \
+    }
 
 int
 Ip::Address::cidr() const
 {
     uint8_t shift,ipbyte;
     uint8_t bit,caught;
