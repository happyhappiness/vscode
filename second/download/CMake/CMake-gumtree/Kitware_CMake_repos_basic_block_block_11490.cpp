{
			case '7':
				if ((memcmp("070707", p, 6) == 0
				    && is_octal(p, odc_header_size))
				    || (memcmp("070727", p, 6) == 0
				        && is_afio_large(p, q - p))) {
					skip = p - (const char *)h;
					__archive_read_consume(a, skip);
					skipped += skip;
					if (p[4] == '2')
						a->archive.archive_format =
						    ARCHIVE_FORMAT_CPIO_AFIO_LARGE;
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