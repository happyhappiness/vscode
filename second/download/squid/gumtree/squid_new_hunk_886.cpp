    struct mstats ms = mstats();
    fprintf(debug_log, "\ttotal space in arena:  %6d KB\n",
            (int) (ms.bytes_total >> 10));
    fprintf(debug_log, "\tTotal free:            %6d KB %d%%\n",
            (int) (ms.bytes_free >> 10),
            Math::intPercent(ms.bytes_free, ms.bytes_total));
#endif
}

void
squid_getrusage(struct rusage *r)
{
    memset(r, '\0', sizeof(struct rusage));
