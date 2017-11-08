apr_status_t file_cleanup(void *thefile)
{
    apr_file_t *file = thefile;
    apr_status_t flush_rv = APR_SUCCESS;

    if (file->filehand != INVALID_HANDLE_VALUE) {

        if (file->buffered) {
            /* XXX: flush here is not mutex protected */
            flush_rv = apr_file_flush((apr_file_t *)thefile);
        }

        /* In order to avoid later segfaults with handle 'reuse',
         * we must protect against the case that a dup2'ed handle
         * is being closed, and invalidate the corresponding StdHandle 
         * We also tell msvcrt when stdhandles are closed.
         */
        if (file->flags & APR_STD_FLAGS)
        {
            if ((file->flags & APR_STD_FLAGS) == APR_STDERR_FLAG) {
                _close(2);
                SetStdHandle(STD_ERROR_HANDLE, INVALID_HANDLE_VALUE);
            }
            else if ((file->flags & APR_STD_FLAGS) == APR_STDOUT_FLAG) {
                _close(1);
                SetStdHandle(STD_OUTPUT_HANDLE, INVALID_HANDLE_VALUE);
            }
            else if ((file->flags & APR_STD_FLAGS) == APR_STDIN_FLAG) {
                _close(0);
                SetStdHandle(STD_INPUT_HANDLE, INVALID_HANDLE_VALUE);
            }
        }
        else
            CloseHandle(file->filehand);

        file->filehand = INVALID_HANDLE_VALUE;
    }
    if (file->pOverlapped && file->pOverlapped->hEvent) {
        CloseHandle(file->pOverlapped->hEvent);
        file->pOverlapped = NULL;
    }
    return flush_rv;
}