				attr |= (plain_attr & BACKGROUND_ALL);
				break;
			default:
				/* Unsupported code */
				break;
			}
			str++;
		} while (*(str-1) == ';');

		set_console_attr();
		break;
	case 'K':
		erase_in_line();
		break;
	default:
		/* Unsupported code */
		break;
	}

	return func + 1;
}

static int ansi_emulate(const char *str, FILE *stream)
{
	int rv = 0;
	const char *pos = str;

	while (*pos) {
		pos = strstr(str, "\033[");
		if (pos) {
			size_t len = pos - str;

			if (len) {
				size_t out_len = fwrite(str, 1, len, stream);
				rv += out_len;
				if (out_len < len)
					return rv;
			}

			str = pos + 2;
			rv += 2;

			fflush(stream);

			pos = set_attr(str);
			rv += pos - str;
			str = pos;
		} else {
			rv += strlen(str);
			fputs(str, stream);
			return rv;
		}
	}
	return rv;
}

int winansi_fputs(const char *str, FILE *stream)
{
	int rv;

	if (!isatty(fileno(stream)))
		return fputs(str, stream);

	init();

	if (!console)
		return fputs(str, stream);

	rv = ansi_emulate(str, stream);

	if (rv >= 0)
		return 0;
	else
		return EOF;
}

static int winansi_vfprintf(FILE *stream, const char *format, va_list list)
{
	int len, rv;
	char small_buf[256];
	char *buf = small_buf;
	va_list cp;

	if (!isatty(fileno(stream)))
		goto abort;

	init();

	if (!console)
		goto abort;

	va_copy(cp, list);
	len = vsnprintf(small_buf, sizeof(small_buf), format, cp);
	va_end(cp);

	if (len > sizeof(small_buf) - 1) {
		buf = malloc(len + 1);
		if (!buf)
			goto abort;

		len = vsnprintf(buf, len + 1, format, list);
	}

	rv = ansi_emulate(buf, stream);

	if (buf != small_buf)
		free(buf);
	return rv;

abort:
	rv = vfprintf(stream, format, list);
	return rv;
}

int winansi_fprintf(FILE *stream, const char *format, ...)
{
	va_list list;
	int rv;

	va_start(list, format);
	rv = winansi_vfprintf(stream, format, list);
	va_end(list);

	return rv;
}

int winansi_printf(const char *format, ...)
{
	va_list list;
	int rv;

	va_start(list, format);
	rv = winansi_vfprintf(stdout, format, list);
	va_end(list);

	return rv;
}
