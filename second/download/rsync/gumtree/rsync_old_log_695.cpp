io_printf(f_out, "@ERROR: failed to open lock file %s : %s\n",
				  lp_lock_file(i), strerror(errno));