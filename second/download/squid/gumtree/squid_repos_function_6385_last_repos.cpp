DiskdActionData&
DiskdActionData::operator += (const DiskdActionData& stats)
{
    sent_count += stats.sent_count;
    recv_count += stats.recv_count;
    if (stats.max_away > max_away)
        max_away = stats.max_away;
    if (stats.max_shmuse > max_shmuse)
        max_shmuse += stats.max_shmuse;
    open_fail_queue_len += stats.open_fail_queue_len;
    block_queue_len += stats.block_queue_len;
    open_ops += stats.open_ops;
    open_success += stats.open_success;
    open_fail += stats.open_fail;
    create_ops += stats.create_ops;
    create_success += stats.create_success;
    create_fail += stats.create_fail;
    close_ops += stats.close_ops;
    close_success += stats.close_success;
    close_fail += stats.close_fail;
    unlink_ops += stats.unlink_ops;
    unlink_success += stats.unlink_success;
    unlink_fail += stats.unlink_fail;
    read_ops += stats.read_ops;
    read_success += stats.read_success;
    read_fail += stats.read_fail;
    write_ops += stats.write_ops;
    write_success += stats.write_success;
    write_fail += stats.write_fail;

    return *this;
}