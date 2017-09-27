 
 
 /* Debugging tools: */
 
 #ifdef APR_RING_DEBUG
 #include <stdio.h>
+#include <assert.h>
+
 #define APR_RING_CHECK_ONE(msg, ptr)					\
 	fprintf(stderr, "*** %s %p\n", msg, ptr)
+
 #define APR_RING_CHECK(hp, elem, link, msg)				\
 	APR_RING_CHECK_ELEM(APR_RING_SENTINEL(hp, elem, link), elem, link, msg)
+
 #define APR_RING_CHECK_ELEM(ep, elem, link, msg) do {			\
 	struct elem *start = (ep);					\
-	struct elem *this = start;					\
+	struct elem *here = start;					\
 	fprintf(stderr, "*** ring check start -- %s\n", msg);		\
 	do {								\
-	    fprintf(stderr, "\telem %p\n", this);			\
+	    fprintf(stderr, "\telem %p\n", here);			\
 	    fprintf(stderr, "\telem->next %p\n",			\
-		    APR_RING_NEXT(this, link));				\
+		    APR_RING_NEXT(here, link));				\
 	    fprintf(stderr, "\telem->prev %p\n",			\
-		    APR_RING_PREV(this, link));				\
+		    APR_RING_PREV(here, link));				\
 	    fprintf(stderr, "\telem->next->prev %p\n",			\
-		    APR_RING_PREV(APR_RING_NEXT(this, link), link));	\
+		    APR_RING_PREV(APR_RING_NEXT(here, link), link));	\
 	    fprintf(stderr, "\telem->prev->next %p\n",			\
-		    APR_RING_NEXT(APR_RING_PREV(this, link), link));	\
-	    if (APR_RING_PREV(APR_RING_NEXT(this, link), link) != this) { \
-		fprintf(stderr, "\t*** this->next->prev != this\n");	\
+		    APR_RING_NEXT(APR_RING_PREV(here, link), link));	\
+	    if (APR_RING_PREV(APR_RING_NEXT(here, link), link) != here) { \
+		fprintf(stderr, "\t*** elem->next->prev != elem\n");	\
 		break;							\
 	    }								\
-	    if (APR_RING_NEXT(APR_RING_PREV(this, link), link) != this) { \
-		fprintf(stderr, "\t*** this->prev->next != this\n");	\
+	    if (APR_RING_NEXT(APR_RING_PREV(here, link), link) != here) { \
+		fprintf(stderr, "\t*** elem->prev->next != elem\n");	\
 		break;							\
 	    }								\
-	    this = APR_RING_NEXT(this, link);				\
-	} while (this != start);					\
+	    here = APR_RING_NEXT(here, link);				\
+	} while (here != start);					\
 	fprintf(stderr, "*** ring check end\n");			\
     } while (0)
+
+#define APR_RING_CHECK_CONSISTENCY(hp, elem, link)			\
+	APR_RING_CHECK_ELEM_CONSISTENCY(APR_RING_SENTINEL(hp, elem, link),\
+					elem, link)
+
+#define APR_RING_CHECK_ELEM_CONSISTENCY(ep, elem, link) do {		\
+	struct elem *start = (ep);					\
+	struct elem *here = start;					\
+	do {								\
+	    assert(APR_RING_PREV(APR_RING_NEXT(here, link), link) == here); \
+	    assert(APR_RING_NEXT(APR_RING_PREV(here, link), link) == here); \
+	    here = APR_RING_NEXT(here, link);				\
+	} while (here != start);					\
+    } while (0)
+
 #else
 /**
  * Print a single pointer value to STDERR
  *   (This is a no-op unless APR_RING_DEBUG is defined.)
  * @param msg Descriptive message
  * @param ptr Pointer value to print
