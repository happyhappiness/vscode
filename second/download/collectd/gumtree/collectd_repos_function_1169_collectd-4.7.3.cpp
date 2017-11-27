int cu_tail_read (cu_tail_t *obj, char *buf, int buflen, tailfunc_t *callback,
		void *data)
{
	int status;

	while (42)
	{
		status = cu_tail_readline (obj, buf, buflen);
		if (status != 0)
		{
			ERROR ("utils_tail: cu_tail_read: cu_tail_readline "
					"failed.");
			break;
		}

		/* check for EOF */
		if (buf[0] == 0)
			break;

		status = callback (data, buf, buflen);
		if (status != 0)
		{
			ERROR ("utils_tail: cu_tail_read: callback returned "
					"status %i.", status);
			break;
		}
	}

	return status;
}