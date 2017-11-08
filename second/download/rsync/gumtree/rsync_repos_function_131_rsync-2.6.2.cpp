void close_batch_delta_file(void)
{
	close(f_delta);
	f_delta = -1;
}