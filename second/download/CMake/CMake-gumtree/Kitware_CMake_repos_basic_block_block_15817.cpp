{
			uint32_t seg;

			iso9660->opt.boot_load_seg = 0;
			if (value == NULL)
				goto invalid_value;
			seg = 0;
			p = value;
			if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
				p += 2;
			while (*p) {
				if (seg)
					seg <<= 4;
				if (*p >= 'A' && *p <= 'F')
					seg += *p - 'A' + 0x0a;
				else if (*p >= 'a' && *p <= 'f')
					seg += *p - 'a' + 0x0a;
				else if (*p >= '0' && *p <= '9')
					seg += *p - '0';
				else
					goto invalid_value;
				if (seg > 0xffff) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Invalid value(over 0xffff) for "
					    "option ``%s''", key);
					return (ARCHIVE_FATAL);
				}
				p++;
			}
			iso9660->el_torito.boot_load_seg = (uint16_t)seg;
			iso9660->opt.boot_load_seg = 1;
			return (ARCHIVE_OK);
		}