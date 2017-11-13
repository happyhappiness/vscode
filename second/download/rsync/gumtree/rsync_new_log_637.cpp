io_printf(fd,"@ERROR: failed to open lock file %s : %s\n",
				  lp_lock_file(), strerror(errno));