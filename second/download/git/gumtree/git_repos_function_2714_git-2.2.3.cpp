static void rerere_io_putmem(const char *mem, size_t sz, struct rerere_io *io)
{
	if (io->output)
		ferr_write(mem, sz, io->output, &io->wrerror);
}