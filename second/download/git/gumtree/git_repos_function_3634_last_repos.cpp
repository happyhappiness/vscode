static unsigned get_prn(unsigned count) {
	count = count * 1103515245 + 12345;
	return (count/65536) % PRN_MODULO;
}