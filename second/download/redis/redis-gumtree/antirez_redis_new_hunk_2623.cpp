			 */
			CONF_HANDLE_SIZE_T(opt_lg_chunk, "lg_chunk", LG_PAGE +
			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1)
			if (strncmp("dss", k, klen) == 0) {
				int i;
				bool match = false;
				for (i = 0; i < dss_prec_limit; i++) {
					if (strncmp(dss_prec_names[i], v, vlen)
					    == 0) {
						if (chunk_dss_prec_set(i)) {
							malloc_conf_error(
							    "Error setting dss",
							    k, klen, v, vlen);
						} else {
							opt_dss =
							    dss_prec_names[i];
							match = true;
							break;
						}
					}
				}
				if (match == false) {
					malloc_conf_error("Invalid conf value",
					    k, klen, v, vlen);
				}
				continue;
			}
			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
			    SIZE_T_MAX)
			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
