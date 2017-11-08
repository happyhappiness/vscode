static void hdr_int(const char *name, uintmax_t value)
{
	format_write(1, "%s: %" PRIuMAX "\r\n", name, value);
}