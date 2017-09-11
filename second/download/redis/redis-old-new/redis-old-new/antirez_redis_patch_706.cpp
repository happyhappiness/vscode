@@ -1,6 +1,6 @@
-/* strbuf - string buffer routines
+/* strbuf - String buffer routines
  *
- * Copyright (c) 2010-2011  Mark Pulford <mark@kyne.com.au>
+ * Copyright (c) 2010-2012  Mark Pulford <mark@kyne.com.au>
  *
  * Permission is hereby granted, free of charge, to any person obtaining
  * a copy of this software and associated documentation files (the
@@ -29,7 +29,7 @@
 
 #include "strbuf.h"
 
-void die(const char *fmt, ...)
+static void die(const char *fmt, ...)
 {
     va_list arg;
 