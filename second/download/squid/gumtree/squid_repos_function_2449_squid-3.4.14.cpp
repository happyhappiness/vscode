int
ipcache_entry::age() const
{
    return request_time.tv_sec ? tvSubMsec(request_time, current_time) : -1;
}