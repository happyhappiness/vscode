 				CONF_HANDLE_BOOL(opt_prof_leak, "prof_leak",
 				    true)
 			}
 			malloc_conf_error("Invalid conf pair", k, klen, v,
 			    vlen);
 #undef CONF_MATCH
-#undef CONF_MATCH_VALUE
 #undef CONF_HANDLE_BOOL
-#undef CONF_MIN_no
-#undef CONF_MIN_yes
-#undef CONF_MAX_no
-#undef CONF_MAX_yes
-#undef CONF_HANDLE_T_U
-#undef CONF_HANDLE_UNSIGNED
 #undef CONF_HANDLE_SIZE_T
 #undef CONF_HANDLE_SSIZE_T
 #undef CONF_HANDLE_CHAR_P
 		}
 	}
 }
 
+/* init_lock must be held. */
 static bool
 malloc_init_hard_needed(void)
 {
 
 	if (malloc_initialized() || (IS_INITIALIZER && malloc_init_state ==
 	    malloc_init_recursible)) {
