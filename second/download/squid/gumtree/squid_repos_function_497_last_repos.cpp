void tvAdd(struct timeval &res, struct timeval const &t1, struct timeval const &t2)
{
    res.tv_sec = t1.tv_sec + t2.tv_sec;
    res.tv_usec = t1.tv_usec + t2.tv_usec;
    if (res.tv_usec >= 1000000) {
        ++res.tv_sec;
        res.tv_usec -= 1000000;
    }
}