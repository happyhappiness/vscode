static apr_status_t make_sparse_file(apr_file_t *file)
{
    BY_HANDLE_FILE_INFORMATION info;
    apr_status_t rv;
    DWORD bytesread = 0;
    DWORD res;

    /* test */

    if (GetFileInformationByHandle(file->filehand, &info)
            && (info.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE))
        return APR_SUCCESS;

    if (file->pOverlapped) {
        file->pOverlapped->Offset     = 0;
        file->pOverlapped->OffsetHigh = 0;
    }

    if (DeviceIoControl(file->filehand, FSCTL_SET_SPARSE, NULL, 0, NULL, 0,
                        &bytesread, file->pOverlapped)) {
        rv = APR_SUCCESS;
    }
    else 
    {
        rv = apr_get_os_error();

        if (rv == APR_FROM_OS_ERROR(ERROR_IO_PENDING))
        {
            do {
                res = WaitForSingleObject(file->pOverlapped->hEvent, 
                                          (file->timeout > 0)
                                            ? (DWORD)(file->timeout/1000)
                                            : ((file->timeout == -1) 
                                                 ? INFINITE : 0));
            } while (res == WAIT_ABANDONED);

            if (res != WAIT_OBJECT_0) {
                CancelIo(file->filehand);
            }

            if (GetOverlappedResult(file->filehand, file->pOverlapped, 
                                    &bytesread, TRUE))
                rv = APR_SUCCESS;
            else
                rv = apr_get_os_error();
        }
    }
    return rv;
}