VOID CALLBACK IoCompletionRoutine(DWORD dwErrorCode,
                                  DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{

    struct aiocb *aiocbp = (struct aiocb *) lpOverlapped->hEvent;

    aiocbp->aio_sigevent.sigev_notify = dwErrorCode;
    aiocbp->aio_sigevent.sigev_signo = dwNumberOfBytesTransfered;
    debugs(81, 7, "AIO operation complete: errorcode=" << dwErrorCode << " nbytes=" << dwNumberOfBytesTransfered);
    xfree(lpOverlapped);
}