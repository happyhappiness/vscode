static int asyncio(struct aiocb *a)
{
    DBG_BUFF
    int rv;

#ifdef _LP64
#define AIO BPX4AIO
#else
#define AIO BPX1AIO
#endif

    AIO(sizeof(struct aiocb), a, &rv, &errno, __err2ad());
    DBG2(4, "BPX4AIO aiocb %p rv %d\n",
             a, rv);
#ifdef DEBUG
    if (rv < 0) {
        DBG2(4, "errno %d errnojr %08x\n",
                 errno, *__err2ad());
    }
#endif
    return rv;
}