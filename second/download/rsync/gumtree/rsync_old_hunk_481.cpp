		}
	}
	if (maxlen == 0) {
		*buf = 0;
		return 0;
	}
	return 1;
}


void io_printf(int fd, const char *format, ...)
{
