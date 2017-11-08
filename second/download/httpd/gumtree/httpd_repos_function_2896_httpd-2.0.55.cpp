static apr_status_t pipenonblock(apr_file_t *thepipe)
{
#ifdef USE_FLAGS
	int				err;
	unsigned long	flags;

    errno = 0;
	if (fcntl(thepipe->filedes, F_GETFL, &flags) != -1)
	{
		flags |= FNDELAY;
		fcntl(thepipe->filedes, F_SETFL, flags);
	}
#else
        errno = 0;
		fcntl(thepipe->filedes, F_SETFL, FNDELAY);
#endif

    if (errno)
        return errno;

    thepipe->blocking = BLK_OFF;
    return APR_SUCCESS;
}