void write_int_named(int f, int32 x, const char *phase)
{
	io_write_phase = phase;
	write_int(f, x);
	io_write_phase = phase_unknown;
}