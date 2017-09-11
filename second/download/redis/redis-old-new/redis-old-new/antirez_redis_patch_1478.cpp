@@ -1,19 +1,29 @@
 #include <stdio.h>
 #include <stdlib.h>
+#include <unistd.h>
 #include <string.h>
+#include <assert.h>
 
 #define	JEMALLOC_MANGLE
 #include "jemalloc_test.h"
 
 int
 main(void)
 {
+	size_t pagesize;
 	void *p, *q;
 	size_t sz, tsz;
 	int r;
 
 	fprintf(stderr, "Test begin\n");
 
+	/* Get page size. */
+	{
+		long result = sysconf(_SC_PAGESIZE);
+		assert(result != -1);
+		pagesize = (size_t)result;
+	}
+
 	r = JEMALLOC_P(allocm)(&p, &sz, 42, 0);
 	if (r != ALLOCM_SUCCESS) {
 		fprintf(stderr, "Unexpected allocm() error\n");
@@ -66,7 +76,7 @@ main(void)
 	p = q;
 	sz = tsz;
 
-	r = JEMALLOC_P(rallocm)(&q, &tsz, 8192, 0, 0);
+	r = JEMALLOC_P(rallocm)(&q, &tsz, pagesize*2, 0, 0);
 	if (r != ALLOCM_SUCCESS)
 		fprintf(stderr, "Unexpected rallocm() error\n");
 	if (q == p)
@@ -78,7 +88,7 @@ main(void)
 	p = q;
 	sz = tsz;
 
-	r = JEMALLOC_P(rallocm)(&q, &tsz, 16384, 0, 0);
+	r = JEMALLOC_P(rallocm)(&q, &tsz, pagesize*4, 0, 0);
 	if (r != ALLOCM_SUCCESS)
 		fprintf(stderr, "Unexpected rallocm() error\n");
 	if (tsz == sz) {
@@ -88,7 +98,7 @@ main(void)
 	p = q;
 	sz = tsz;
 
-	r = JEMALLOC_P(rallocm)(&q, &tsz, 8192, 0, ALLOCM_NO_MOVE);
+	r = JEMALLOC_P(rallocm)(&q, &tsz, pagesize*2, 0, ALLOCM_NO_MOVE);
 	if (r != ALLOCM_SUCCESS)
 		fprintf(stderr, "Unexpected rallocm() error\n");
 	if (q != p)
@@ -99,7 +109,7 @@ main(void)
 	}
 	sz = tsz;
 
-	r = JEMALLOC_P(rallocm)(&q, &tsz, 16384, 0, ALLOCM_NO_MOVE);
+	r = JEMALLOC_P(rallocm)(&q, &tsz, pagesize*4, 0, ALLOCM_NO_MOVE);
 	if (r != ALLOCM_SUCCESS)
 		fprintf(stderr, "Unexpected rallocm() error\n");
 	if (q != p)