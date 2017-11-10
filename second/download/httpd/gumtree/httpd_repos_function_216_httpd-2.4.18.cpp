static int dav_fs_lock_expired(time_t expires)
{
    return expires != DAV_TIMEOUT_INFINITE && time(NULL) >= expires;
}