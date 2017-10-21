	va_end(ap);

	if (len < 0) exit_cleanup(1);

	write_sbuf(fd, buf);
}
