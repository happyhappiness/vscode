static apr_status_t socket_pipe_cleanup(void *thefile)
{
    apr_file_t *file = thefile;
    if (file->filehand != INVALID_HANDLE_VALUE) {
        shutdown((SOCKET)file->filehand, SD_BOTH);
        closesocket((SOCKET)file->filehand);
        file->filehand = INVALID_HANDLE_VALUE;
    }
    return APR_SUCCESS;
}