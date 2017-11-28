void
DiskDaemonDiskIOModule::Stats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "sent_count: %d\n", diskd_stats.sent_count);
    storeAppendPrintf(sentry, "recv_count: %d\n", diskd_stats.recv_count);
    storeAppendPrintf(sentry, "max_away: %d\n", diskd_stats.max_away);
    storeAppendPrintf(sentry, "max_shmuse: %d\n", diskd_stats.max_shmuse);
    storeAppendPrintf(sentry, "open_fail_queue_len: %d\n", diskd_stats.open_fail_queue_len);
    storeAppendPrintf(sentry, "block_queue_len: %d\n", diskd_stats.block_queue_len);
    diskd_stats.max_away = diskd_stats.max_shmuse = 0;
    storeAppendPrintf(sentry, "\n              OPS   SUCCESS    FAIL\n");
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "open", diskd_stats.open.ops, diskd_stats.open.success, diskd_stats.open.fail);
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "create", diskd_stats.create.ops, diskd_stats.create.success, diskd_stats.create.fail);
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "close", diskd_stats.close.ops, diskd_stats.close.success, diskd_stats.close.fail);
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "unlink", diskd_stats.unlink.ops, diskd_stats.unlink.success, diskd_stats.unlink.fail);
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "read", diskd_stats.read.ops, diskd_stats.read.success, diskd_stats.read.fail);
    storeAppendPrintf(sentry, "%7s %9d %9d %7d\n",
                      "write", diskd_stats.write.ops, diskd_stats.write.success, diskd_stats.write.fail);
}