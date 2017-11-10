static apr_status_t read_with_timeout(apr_file_t *file, void *buf, apr_size_t len_in, apr_size_t *nbytes)
{
    apr_status_t rv;
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

    rv = ReadFile(file->filehand, buf, len, 
                  &bytesread, file->pOverlapped);
    *nbytes = bytesread;

    if (!rv) {
        rv = apr_get_os_error();
        if (rv == APR_FROM_OS_ERROR(ERROR_IO_PENDING)) {
            /* Wait for the pending i/o */
            if (file->timeout > 0) {
                /* timeout in milliseconds... */
                rv = WaitForSingleObject(file->pOverlapped->hEvent, 
                                         (DWORD)(file->timeout/1000)); 
            }
            else if (file->timeout == -1) {
                rv = WaitForSingleObject(file->pOverlapped->hEvent, INFINITE);
            }
            switch (rv) {
                case WAIT_OBJECT_0:
                    GetOverlappedResult(file->filehand, file->pOverlapped, 
                                        &bytesread, TRUE);
                    *nbytes = bytesread;
                    rv = APR_SUCCESS;
                    break;

                case WAIT_TIMEOUT:
                    rv = APR_TIMEUP;
                    break;

                case WAIT_FAILED:
                    rv = apr_get_os_error();
                    break;

                default:
                    break;
            }

            if (rv != APR_SUCCESS) {
                if (apr_os_level >= APR_WIN_98) {
                    CancelIo(file->filehand);
                }
            }
        }
        else if (rv == APR_FROM_OS_ERROR(ERROR_BROKEN_PIPE)) {
            /* Assume ERROR_BROKEN_PIPE signals an EOF reading from a pipe */
            rv = APR_EOF;
        } else if (rv == APR_FROM_OS_ERROR(ERROR_HANDLE_EOF)) {
            /* Did we hit EOF reading from the handle? */
            rv = APR_EOF;
        }
    } else {
        /* OK and 0 bytes read ==> end of file */
        if (*nbytes == 0)
            rv = APR_EOF;
        else
            rv = APR_SUCCESS;
    }
    if (rv == APR_SUCCESS && file->pOverlapped && !file->pipe) {
        file->filePtr += *nbytes;
    }
    return rv;
}