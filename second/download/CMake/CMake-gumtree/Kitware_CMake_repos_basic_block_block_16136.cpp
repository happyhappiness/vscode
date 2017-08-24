(iso9660->opt.boot_load_size != OPT_BOOT_LOAD_SIZE_DEFAULT)
		set_option_info(&info, &opt, "boot-load-size",
		    KEY_INT, iso9660->el_torito.boot_load_size)