     }
 
     /* NOTREACHED */
     return 0;
 }
 
-#else
-#include <stdio.h>
+#else /* !USE_ICMP */
+
+#include <ostream>
 int
 main(int argc, char *argv[])
 {
-    fprintf(stderr, "%s: ICMP support not compiled in.\n", argv[0]);
+    std::cerr << argv[0] << ": ICMP support not compiled in." << std::endl;
     return 1;
 }
 
 #endif /* USE_ICMP */
+
