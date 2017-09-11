			 */
			CONF_HANDLE_SIZE_T(opt_lg_chunk, "lg_chunk", LG_PAGE +
			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1)
			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
			    SIZE_T_MAX)
			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
