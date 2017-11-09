static void set_packet_header(char *buf, const int size)
{
	static char hexchar[] = "0123456789abcdef";

	#define hex(a) (hexchar[(a) & 15])
	buf[0] = hex(size >> 12);
	buf[1] = hex(size >> 8);
	buf[2] = hex(size >> 4);
	buf[3] = hex(size);
	#undef hex
}