					malloc_conf_error("Invalid conf value",
					    k, klen, v, vlen);
				}
				continue;
			}
			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
			    SIZE_T_MAX)
			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
			    -1, (sizeof(size_t) << 3) - 1)
			CONF_HANDLE_BOOL(opt_stats_print, "stats_print")
			if (config_fill) {
				CONF_HANDLE_BOOL(opt_junk, "junk")
				CONF_HANDLE_SIZE_T(opt_quarantine, "quarantine",
				    0, SIZE_T_MAX)
				CONF_HANDLE_BOOL(opt_redzone, "redzone")
				CONF_HANDLE_BOOL(opt_zero, "zero")
			}
			if (config_utrace) {
				CONF_HANDLE_BOOL(opt_utrace, "utrace")
			}
