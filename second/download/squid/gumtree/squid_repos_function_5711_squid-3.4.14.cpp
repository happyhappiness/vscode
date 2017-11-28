void
DiskdIOStrategy::openFailed()
{
    ++diskd_stats.open_fail_queue_len;
}