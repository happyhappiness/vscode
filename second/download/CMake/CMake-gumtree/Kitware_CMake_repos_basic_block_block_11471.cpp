{
			case '1':
			case '2':
				if (memcmp("07070", p, 5) == 0
				    && is_hex(p, newc_header_size)) {
					skip = p - (const char *)h;
					__archive_read_consume(a, skip);
					skipped += skip;
					if (skipped > 0) {
						archive_set_error(&a->archive,
						    0,
						    "Skipped %d bytes before "
						    "finding valid header",
						    (int)skipped);
						return (ARCHIVE_WARN);
					}
					return (ARCHIVE_OK);
				}
				p += 2;
				break;
			case '0':
				p++;
				break;
			default:
				p += 6;
				break;
			}