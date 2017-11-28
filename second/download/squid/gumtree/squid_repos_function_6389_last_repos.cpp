void
DiskdAction::dump(StoreEntry* entry)
{
    debugs(79, 5, HERE);
    Must(entry != NULL);
    storeAppendPrintf(entry, "sent_count: %.0f\n", data.sent_count);
    storeAppendPrintf(entry, "recv_count: %.0f\n", data.recv_count);
    storeAppendPrintf(entry, "max_away: %.0f\n", data.max_away);
    storeAppendPrintf(entry, "max_shmuse: %.0f\n", data.max_shmuse);
    storeAppendPrintf(entry, "open_fail_queue_len: %.0f\n", data.open_fail_queue_len);
    storeAppendPrintf(entry, "block_queue_len: %.0f\n", data.block_queue_len);
    storeAppendPrintf(entry, "\n              OPS   SUCCESS    FAIL\n");
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "open", data.open_ops, data.open_success, data.open_fail);
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "create", data.create_ops, data.create_success, data.create_fail);
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "close", data.close_ops, data.close_success, data.close_fail);
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "unlink", data.unlink_ops, data.unlink_success, data.unlink_fail);
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "read", data.read_ops, data.read_success, data.read_fail);
    storeAppendPrintf(entry, "%7s %9.0f %9.0f %7.0f\n",
                      "write", data.write_ops, data.write_success, data.write_fail);
}