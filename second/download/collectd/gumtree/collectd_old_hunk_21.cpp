
	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	syslog (level, message);
}
