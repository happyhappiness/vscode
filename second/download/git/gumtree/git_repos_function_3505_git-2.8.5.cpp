void set_error_handle(FILE *fh)
{
	error_handle = fh;
	tweaked_error_buffering = 0;
}