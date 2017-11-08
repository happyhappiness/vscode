static apr_status_t pipeblock(apr_file_t *thepipe)
{
#ifdef USE_FLAGS
    int				err;
	unsigned long	flags;

	if (fcntl(thepipe->filedes, F_GETFL, &flags) != -1)
	{
		flags &= ~FNDELAY;
		fcntl(thepipe->filedes, F_SETFL, flags);
	}
#else
        errno = 0;
		fcntl(thepipe->filedes, F_SETFL, 0);
#endif

    if (errno)
        return errno;

    thepipe->blocking = BLK_ON;
    return APR_SUCCESS;
}