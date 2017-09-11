@@ -748,7 +748,7 @@ stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
 						ninitialized++;
 				}
 
-				if (ninitialized > 1) {
+				if (ninitialized > 1 || unmerged == false) {
 					/* Print merged arena stats. */
 					malloc_cprintf(write_cb, cbopaque,
 					    "\nMerged arenas stats:\n");