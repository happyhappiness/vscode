void close_batch_csums_file(void)
{
	close(f_csums);
	f_csums = -1;
}