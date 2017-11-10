apr_status_t apr_file_lock(apr_file_t *thefile, int type)
{
	int fc;

	fc = (type & APR_FLOCK_NONBLOCK) ? NX_RANGE_LOCK_TRYLOCK : NX_RANGE_LOCK_CHECK;

    if(NXFileRangeLock(thefile->filedes,fc, 0, 0) == -1)
		return errno;
            
    return APR_SUCCESS;
}