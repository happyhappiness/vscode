static int milli_diff(const struct timeval *t1, const struct timeval *t2)
{
    int64_t ret;
    int sec_diff = t1->tv_sec - t2->tv_sec;
    int usec_diff = t1->tv_usec - t2->tv_usec;
    ret = usec_diff / 1000;
    ret += (sec_diff * 1000);
    return (ret > INT_MAX) ? INT_MAX : ((ret < INT_MIN) ? INT_MIN : (int)ret);
}