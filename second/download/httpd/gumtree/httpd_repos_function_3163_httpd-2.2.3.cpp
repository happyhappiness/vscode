apr_status_t apr_file_unlock(apr_file_t *thefile)
{
    if(NXFileRangeUnlock(thefile->filedes,NX_RANGE_LOCK_CANCEL,0 , 0) == -1)
		return errno;
   
    return APR_SUCCESS;
}