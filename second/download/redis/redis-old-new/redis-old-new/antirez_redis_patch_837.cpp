@@ -43,7 +43,7 @@ pages_map(void *addr, size_t size)
 		if (munmap(ret, size) == -1) {
 			char buf[BUFERROR_BUF];
 
-			buferror(buf, sizeof(buf));
+			buferror(get_errno(), buf, sizeof(buf));
 			malloc_printf("<jemalloc: Error in munmap(): %s\n",
 			    buf);
 			if (opt_abort)
@@ -69,7 +69,7 @@ pages_unmap(void *addr, size_t size)
 	{
 		char buf[BUFERROR_BUF];
 
-		buferror(buf, sizeof(buf));
+		buferror(get_errno(), buf, sizeof(buf));
 		malloc_printf("<jemalloc>: Error in "
 #ifdef _WIN32
 		              "VirtualFree"