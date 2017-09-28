				if (!match) {
					malloc_conf_error("Invalid conf value",
					    k, klen, v, vlen);
				}
				continue;
			}
			CONF_HANDLE_UNSIGNED(opt_narenas, "narenas", 1,
			    UINT_MAX, yes, no, false)
			if (strncmp("purge", k, klen) == 0) {
				int i;
				bool match = false;
				for (i = 0; i < purge_mode_limit; i++) {
					if (strncmp(purge_mode_names[i], v,
					    vlen) == 0) {
						opt_purge = (purge_mode_t)i;
						match = true;
						break;
					}
				}
				if (!match) {
					malloc_conf_error("Invalid conf value",
					    k, klen, v, vlen);
				}
				continue;
			}
			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
			    -1, (sizeof(size_t) << 3) - 1)
			CONF_HANDLE_SSIZE_T(opt_decay_time, "decay_time", -1,
			    NSTIME_SEC_MAX);
			CONF_HANDLE_BOOL(opt_stats_print, "stats_print", true)
			if (config_fill) {
				if (CONF_MATCH("junk")) {
					if (CONF_MATCH_VALUE("true")) {
						if (config_valgrind &&
						    unlikely(in_valgrind)) {
							malloc_conf_error(
							"Deallocation-time "
							"junk filling cannot "
							"be enabled while "
							"running inside "
							"Valgrind", k, klen, v,
							vlen);
						} else {
							opt_junk = "true";
							opt_junk_alloc = true;
							opt_junk_free = true;
						}
					} else if (CONF_MATCH_VALUE("false")) {
						opt_junk = "false";
						opt_junk_alloc = opt_junk_free =
						    false;
					} else if (CONF_MATCH_VALUE("alloc")) {
						opt_junk = "alloc";
						opt_junk_alloc = true;
						opt_junk_free = false;
					} else if (CONF_MATCH_VALUE("free")) {
						if (config_valgrind &&
						    unlikely(in_valgrind)) {
							malloc_conf_error(
							"Deallocation-time "
							"junk filling cannot "
							"be enabled while "
							"running inside "
							"Valgrind", k, klen, v,
							vlen);
						} else {
							opt_junk = "free";
							opt_junk_alloc = false;
							opt_junk_free = true;
						}
					} else {
						malloc_conf_error(
						    "Invalid conf value", k,
						    klen, v, vlen);
					}
					continue;
				}
				CONF_HANDLE_SIZE_T(opt_quarantine, "quarantine",
				    0, SIZE_T_MAX, no, no, false)
				CONF_HANDLE_BOOL(opt_redzone, "redzone", true)
				CONF_HANDLE_BOOL(opt_zero, "zero", true)
			}
			if (config_utrace) {
				CONF_HANDLE_BOOL(opt_utrace, "utrace", true)
			}
