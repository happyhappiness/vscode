void
DiskdAction::collect()
{
    data.sent_count = diskd_stats.sent_count;
    data.recv_count = diskd_stats.recv_count;
    data.max_away = diskd_stats.max_away;
    data.max_shmuse = diskd_stats.max_shmuse;
    data.open_fail_queue_len = diskd_stats.open_fail_queue_len;
    data.block_queue_len = diskd_stats.block_queue_len;
    diskd_stats.max_away = diskd_stats.max_shmuse = 0;

    data.open_ops = diskd_stats.open.ops;
    data.open_success = diskd_stats.open.success;
    data.open_fail = diskd_stats.open.fail;

    data.create_ops = diskd_stats.create.ops;
    data.create_success = diskd_stats.create.success;
    data.create_fail = diskd_stats.create.fail;

    data.close_ops = diskd_stats.close.ops;
    data.close_success = diskd_stats.close.success;
    data.close_fail = diskd_stats.close.fail;

    data.unlink_ops = diskd_stats.unlink.ops;
    data.unlink_success = diskd_stats.unlink.success;
    data.unlink_fail = diskd_stats.unlink.fail;

    data.read_ops = diskd_stats.read.ops;
    data.read_success = diskd_stats.read.success;
    data.read_fail = diskd_stats.read.fail;

    data.write_ops = diskd_stats.write.ops;
    data.write_success = diskd_stats.write.success;
    data.write_fail = diskd_stats.write.fail;
}