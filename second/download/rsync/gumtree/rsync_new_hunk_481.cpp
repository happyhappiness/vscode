		}
	}
	if (maxlen == 0) {
		*buf = 0;
		return 0;
	}

	eof_error = 1;

	return 1;
}


void io_printf(int fd, const char *format, ...)
{
