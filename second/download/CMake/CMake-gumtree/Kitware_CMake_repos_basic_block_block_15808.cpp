{
			int num = 0;
			r = get_num_opt(a, &num, 0xffff, 1, key, value);
			iso9660->opt.boot_load_size = r == ARCHIVE_OK;
			if (r != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			iso9660->el_torito.boot_load_size = (uint16_t)num;
			return (ARCHIVE_OK);
		}