static apr_status_t read_with_timeout(apr_file_t *file, void *buf, apr_size_t len_in, apr_size_t *nbytes)
{
    apr_status_t rv;
    DWORD res;
    DWORD len = (DWORD)len_in;
    DWORD bytesread = 0;

    /* Handle the zero timeout non-blocking case */
    if (file->timeout == 0) {
        /* Peek at the pipe. If there is no data available, return APR_EAGAIN.
         * If data is available, go ahead and read it.
         */
        if (file->pipe) {
            DWORD bytes;
            if (!PeekNamedPipe(file->filehand, NULL, 0, NULL, &bytes, NULL)) {
                rv = apr_get_os_error();
                if (rv == APR_FROM_OS_ERROR(ERROR_BROKEN_PIPE)) {
                    rv = APR_EOF;
                }
                *nbytes = 0;
                return rv;
            }
            else {
                if (bytes == 0) {
                    *nbytes = 0;
                    return APR_EAGAIN;
                }
                if (len > bytes) {
                    len = bytes;
                }
            }
        }
        else {
            /* ToDo: Handle zero timeout non-blocking file i/o 
             * This is not needed until an APR application needs to
             * timeout file i/o (which means setting file i/o non-blocking)
             */
        }
    }

    if (file->pOverlapped && !file->pipe) {
        file->pOverlapped->Offset     = (DWORD)file->filePtr;
        file->pOverlapped->OffsetHigh = (DWORD)(file->filePtr >> 32);
    }

    if (ReadFile(file->filehand, buf, len, 
                 &bytesread, file->pOverlapped)) {
        rv = APR_SUCCESS;
    }
    else {
        rv = apr_get_os_error();
        if (rv == APR_FROM_OS_ERROR(ERROR_IO_PENDING)) {
            /* Wait for the pending i/o, timeout converted from us to ms
             * Note that we loop if someone gives up the event, since
             * folks suggest that WAIT_ABANDONED isn't actually a result
             * but an alert that ownership of the event has passed from
             * one owner to a new proc/thread.
             */
            do {
                res = WaitForSingleObject(file->pOverlapped->hEvent, 
                                          (file->timeout > 0)
                                            ? (DWORD)(file->timeout/1000)
                                            : ((file->timeout == -1) 
                                                 ? INFINITE : 0));
            } while (res == WAIT_ABANDONED);

            /* There is one case that represents entirely
             * successful operations, otherwise we will cancel
             * the operation in progress.
             */
            if (res != WAIT_OBJECT_0) {
                CancelIo(file->filehand);
            }

            /* Ignore any failures above.  Attempt to complete
             * the overlapped operation and use only _its_ result.
             * For example, CancelIo or WaitForSingleObject can
             * fail if the handle is closed, yet the read may have
             * completed before we attempted to CancelIo...
             */
            if (GetOverlappedResult(file->filehand, file->pOverlapped, 
                                    &bytesread, TRUE)) {
                rv = APR_SUCCESS;
            }
            else {
                rv = apr_get_os_error();
                if (((rv == APR_FROM_OS_ERROR(ERROR_IO_INCOMPLETE))
                        || (rv == APR_FROM_OS_ERROR(ERROR_OPERATION_ABORTED)))
                    && (res == WAIT_TIMEOUT))
                    rv = APR_TIMEUP;
            }
        }
        if (rv == APR_FROM_OS_ERROR(ERROR_BROKEN_PIPE)) {
            /* Assume ERROR_BROKEN_PIPE signals an EOF reading from a pipe */
            rv = APR_EOF;
        } else if (rv == APR_FROM_OS_ERROR(ERROR_HANDLE_EOF)) {
            /* Did we hit EOF reading from the handle? */
            rv = APR_EOF;
        }
    }
    
    /* OK and 0 bytes read ==> end of file */
    if (rv == APR_SUCCESS && bytesread == 0)
        rv = APR_EOF;
    
    if (rv == APR_SUCCESS && file->pOverlapped && !file->pipe) {
        file-