 							    dss_prec_names[i];
 							match = true;
 							break;
 						}
 					}
 				}
-				if (match == false) {
+				if (!match) {
 					malloc_conf_error("Invalid conf value",
 					    k, klen, v, vlen);
 				}
 				continue;
 			}
 			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
 			    SIZE_T_MAX, false)
 			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
 			    -1, (sizeof(size_t) << 3) - 1)
-			CONF_HANDLE_BOOL(opt_stats_print, "stats_print")
+			CONF_HANDLE_BOOL(opt_stats_print, "stats_print", true)
 			if (config_fill) {
-				CONF_HANDLE_BOOL(opt_junk, "junk")
+				if (CONF_MATCH("junk")) {
+					if (CONF_MATCH_VALUE("true")) {
+						opt_junk = "true";
+						opt_junk_alloc = opt_junk_free =
+						    true;
+					} else if (CONF_MATCH_VALUE("false")) {
+						opt_junk = "false";
+						opt_junk_alloc = opt_junk_free =
+						    false;
+					} else if (CONF_MATCH_VALUE("alloc")) {
+						opt_junk = "alloc";
+						opt_junk_alloc = true;
+						opt_junk_free = false;
+					} else if (CONF_MATCH_VALUE("free")) {
+						opt_junk = "free";
+						opt_junk_alloc = false;
+						opt_junk_free = true;
+					} else {
+						malloc_conf_error(
+						    "Invalid conf value", k,
+						    klen, v, vlen);
+					}
+					continue;
+				}
 				CONF_HANDLE_SIZE_T(opt_quarantine, "quarantine",
 				    0, SIZE_T_MAX, false)
-				CONF_HANDLE_BOOL(opt_redzone, "redzone")
-				CONF_HANDLE_BOOL(opt_zero, "zero")
+				CONF_HANDLE_BOOL(opt_redzone, "redzone", true)
+				CONF_HANDLE_BOOL(opt_zero, "zero", true)
 			}
 			if (config_utrace) {
-				CONF_HANDLE_BOOL(opt_utrace, "utrace")
-			}
-			if (config_valgrind) {
-				CONF_HANDLE_BOOL(opt_valgrind, "valgrind")
+				CONF_HANDLE_BOOL(opt_utrace, "utrace", true)
 			}
 			if (config_xmalloc) {
-				CONF_HANDLE_BOOL(opt_xmalloc, "xmalloc")
+				CONF_HANDLE_BOOL(opt_xmalloc, "xmalloc", true)
 			}
 			if (config_tcache) {
-				CONF_HANDLE_BOOL(opt_tcache, "tcache")
+				CONF_HANDLE_BOOL(opt_tcache, "tcache",
+				    !config_valgrind || !in_valgrind)
+				if (CONF_MATCH("tcache")) {
+					assert(config_valgrind && in_valgrind);
+					if (opt_tcache) {
+						opt_tcache = false;
+						malloc_conf_error(
+						"tcache cannot be enabled "
+						"while running inside Valgrind",
+						k, klen, v, vlen);
+					}
+					continue;
+				}
 				CONF_HANDLE_SSIZE_T(opt_lg_tcache_max,
 				    "lg_tcache_max", -1,
 				    (sizeof(size_t) << 3) - 1)
 			}
 			if (config_prof) {
-				CONF_HANDLE_BOOL(opt_prof, "prof")
+				CONF_HANDLE_BOOL(opt_prof, "prof", true)
 				CONF_HANDLE_CHAR_P(opt_prof_prefix,
 				    "prof_prefix", "jeprof")
-				CONF_HANDLE_BOOL(opt_prof_active, "prof_active")
-				CONF_HANDLE_SSIZE_T(opt_lg_prof_sample,
+				CONF_HANDLE_BOOL(opt_prof_active, "prof_active",
+				    true)
+				CONF_HANDLE_BOOL(opt_prof_thread_active_init,
+				    "prof_thread_active_init", true)
+				CONF_HANDLE_SIZE_T(opt_lg_prof_sample,
 				    "lg_prof_sample", 0,
-				    (sizeof(uint64_t) << 3) - 1)
-				CONF_HANDLE_BOOL(opt_prof_accum, "prof_accum")
+				    (sizeof(uint64_t) << 3) - 1, true)
+				CONF_HANDLE_BOOL(opt_prof_accum, "prof_accum",
+				    true)
 				CONF_HANDLE_SSIZE_T(opt_lg_prof_interval,
 				    "lg_prof_interval", -1,
 				    (sizeof(uint64_t) << 3) - 1)
-				CONF_HANDLE_BOOL(opt_prof_gdump, "prof_gdump")
-				CONF_HANDLE_BOOL(opt_prof_final, "prof_final")
-				CONF_HANDLE_BOOL(opt_prof_leak, "prof_leak")
+				CONF_HANDLE_BOOL(opt_prof_gdump, "prof_gdump",
+				    true)
+				CONF_HANDLE_BOOL(opt_prof_final, "prof_final",
+				    true)
+				CONF_HANDLE_BOOL(opt_prof_leak, "prof_leak",
+				    true)
 			}
 			malloc_conf_error("Invalid conf pair", k, klen, v,
 			    vlen);
+#undef CONF_MATCH
 #undef CONF_HANDLE_BOOL
 #undef CONF_HANDLE_SIZE_T
 #undef CONF_HANDLE_SSIZE_T
 #undef CONF_HANDLE_CHAR_P
 		}
 	}
 }
 
+/* init_lock must be held. */
 static bool
-malloc_init_hard(void)
+malloc_init_hard_needed(void)
 {
-	arena_t *init_arenas[1];
 
-	malloc_mutex_lock(&init_lock);
-	if (malloc_initialized || IS_INITIALIZER) {
+	if (malloc_initialized() || (IS_INITIALIZER && malloc_init_state ==
+	    malloc_init_recursible)) {
 		/*
 		 * Another thread initialized the allocator before this one
 		 * acquired init_lock, or this thread is the initializing
 		 * thread, and it is recursively allocating.
 		 */
-		malloc_mutex_unlock(&init_lock);
 		return (false);
 	}
 #ifdef JEMALLOC_THREADED_INIT
-	if (malloc_initializer != NO_INITIALIZER && IS_INITIALIZER == false) {
+	if (malloc_initializer != NO_INITIALIZER && !IS_INITIALIZER) {
 		/* Busy-wait until the initializing thread completes. */
 		do {
 			malloc_mutex_unlock(&init_lock);
 			CPU_SPINWAIT;
 			malloc_mutex_lock(&init_lock);
-		} while (malloc_initialized == false);
-		malloc_mutex_unlock(&init_lock);
+		} while (!malloc_initialized());
 		return (false);
 	}
 #endif
+	return (true);
+}
+
+/* init_lock must be held. */
+static bool
+malloc_init_hard_a0_locked(void)
+{
+
 	malloc_initializer = INITIALIZER;
 
-	malloc_tsd_boot();
 	if (config_prof)
 		prof_boot0();
-
 	malloc_conf_init();
-
 	if (opt_stats_print) {
 		/* Print statistics at exit. */
 		if (atexit(stats_print_atexit) != 0) {
 			malloc_write("<jemalloc>: Error in atexit()\n");
 			if (opt_abort)
 				abort();
