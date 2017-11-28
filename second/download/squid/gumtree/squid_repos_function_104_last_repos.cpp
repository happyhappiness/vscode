void tvAssignAdd(struct timeval &t, struct timeval const &add)
{
    t.tv_sec += add.tv_sec;
    t.tv_usec += add.tv_usec;
    if (t.tv_usec >= 1000000) {
        ++t.tv_sec;
        t.tv_usec -= 1000000;
    }
}