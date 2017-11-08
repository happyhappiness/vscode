apr_status_t file_cleanup(void *thefile)
{
    apr_file_t *file = thefile;
    apr_status_t flush_rv = APR_SUCCESS;

    if (file->filehand != INVALID_HANDLE_VALUE) {

        /* In order to avoid later segfaults with handle 'reuse',
         * we must protect against the case that a dup2'ed handle
         * is being closed, and invalidate the corresponding StdHandle 
         */
        if (file->filehand == GetStdHandle(STD_ERROR_HANDLE)) {
            SetStdHandle(STD_ERROR_HANDLE, INVALID_HANDLE_VALUE);
        }
        if (file->filehand == GetStdHandle(STD_OUTPUT_HANDLE)) {
            SetStdHandle(STD_OUTPUT_HANDLE, INVALID_HANDLE_VALUE);
        }
        if (file->filehand == GetStdHandle(STD_INPUT_HANDLE)) {
            SetStdHandle(STD_INPUT_HANDLE, INVALID_HANDLE_VALUE);
        }

        if (file->buffered) {
            /* XXX: flush here is not mutex protected */
            flush_rv = apr_file_flush((apr_file_t *)thefile);
        }
        CloseHandle(file->filehand);
        file->filehand = INVALID_HANDLE_VALUE;
    }
    if (file->pOverlapped && file->pOverlapped->hEvent) {
        CloseHandle(file->pOverlapped->hEvent);
        file->pOverlapped = NULL;
    }
    return flush_rv;
}