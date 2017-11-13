io_printf(fd,"@ERROR: access denied to %s from %s (%s)\n",
			  name, client_name(fd), client_addr(fd));