int aio_write(struct aiocb *aiocbp)
{
    LPOVERLAPPED Overlapped;
    BOOL IoOperationStatus;

    /* Allocate an overlapped structure. */
    Overlapped = (LPOVERLAPPED) xcalloc(1, sizeof(OVERLAPPED));

    if (!Overlapped) {
        errno = ENOMEM;
        return -1;
    }

#if _FILE_OFFSET_BITS==64
#ifdef __GNUC__
    Overlapped->Offset = (DWORD) (aiocbp->aio_offset % 0x100000000LL);

    Overlapped->OffsetHigh = (DWORD) (aiocbp->aio_offset / 0x100000000LL);

#else

    Overlapped->Offset = (DWORD) (aiocbp->aio_offset % 0x100000000);

    Overlapped->OffsetHigh = (DWORD) (aiocbp->aio_offset / 0x100000000);

#endif
#else

    Overlapped->Offset = aiocbp->aio_offset;

    Overlapped->OffsetHigh = 0;

#endif

    Overlapped->hEvent = aiocbp;

    aiocbp->aio_sigevent.sigev_notify = EINPROGRESS;

    aiocbp->aio_sigevent.sigev_signo = -1;

    IoOperationStatus = WriteFileEx((HANDLE)_get_osfhandle(aiocbp->aio_fildes),
                                    aiocbp->aio_buf,
                                    aiocbp->aio_nbytes,
                                    Overlapped,
                                    IoCompletionRoutine);

    /* Test to see if the I/O was queued successfully. */
    if (!IoOperationStatus) {
        errno = GetLastError();
        debugs(81, DBG_IMPORTANT, "aio_write: GetLastError=" << errno  );
        return -1;
    }

    /* The I/O queued successfully. Go back into the
       alertable wait for I/O completion or for
       more I/O requests. */
    return 0;
}