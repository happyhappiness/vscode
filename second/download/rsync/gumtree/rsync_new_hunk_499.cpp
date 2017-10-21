		rprintf(FERROR,"max connections (%d) reached\n",
			lp_max_connections());
		io_printf(fd,"@ERROR: max connections (%d) reached - try again later\n", lp_max_connections());
		return -1;
	}

	
	module_id = i;

	if (lp_read_only(i))
		read_only = 1;

