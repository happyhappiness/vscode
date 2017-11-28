void
tvSub(struct timeval &res, struct timeval const &t1, struct timeval const &t2)
{
    res.tv_sec = t2.tv_sec - t1.tv_sec;
    if (t2.tv_usec >= t1.tv_usec)
        res.tv_usec = t2.tv_usec - t1.tv_usec;
    else {
        res.tv_sec -= 1;
        res.tv_usec = t2.tv_usec + 1000000 - t1.tv_usec;
    }
}