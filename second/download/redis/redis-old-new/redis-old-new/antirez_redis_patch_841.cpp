@@ -345,25 +345,25 @@ stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
 		malloc_cprintf(write_cb, cbopaque, "Assertions %s\n",
 		    bv ? "enabled" : "disabled");
 
-#define OPT_WRITE_BOOL(n)						\
+#define	OPT_WRITE_BOOL(n)						\
 		if ((err = je_mallctl("opt."#n, &bv, &bsz, NULL, 0))	\
 		    == 0) {						\
 			malloc_cprintf(write_cb, cbopaque,		\
 			    "  opt."#n": %s\n", bv ? "true" : "false");	\
 		}
-#define OPT_WRITE_SIZE_T(n)						\
+#define	OPT_WRITE_SIZE_T(n)						\
 		if ((err = je_mallctl("opt."#n, &sv, &ssz, NULL, 0))	\
 		    == 0) {						\
 			malloc_cprintf(write_cb, cbopaque,		\
 			"  opt."#n": %zu\n", sv);			\
 		}
-#define OPT_WRITE_SSIZE_T(n)						\
+#define	OPT_WRITE_SSIZE_T(n)						\
 		if ((err = je_mallctl("opt."#n, &ssv, &sssz, NULL, 0))	\
 		    == 0) {						\
 			malloc_cprintf(write_cb, cbopaque,		\
 			    "  opt."#n": %zd\n", ssv);			\
 		}
-#define OPT_WRITE_CHAR_P(n)						\
+#define	OPT_WRITE_CHAR_P(n)						\
 		if ((err = je_mallctl("opt."#n, &cpv, &cpsz, NULL, 0))	\
 		    == 0) {						\
 			malloc_cprintf(write_cb, cbopaque,		\