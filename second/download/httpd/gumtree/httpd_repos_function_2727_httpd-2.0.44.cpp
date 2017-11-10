static UCHAR randbyte()
{
    return randbyte_hrtimer() ^ randbyte_sysinfo() ^ randbyte_perf();
}