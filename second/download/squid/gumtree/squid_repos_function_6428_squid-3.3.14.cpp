void
Mgr::StoreIoAction::collect()
{
    data.create_calls = store_io_stats.create.calls;
    data.create_select_fail = store_io_stats.create.select_fail;
    data.create_create_fail = store_io_stats.create.create_fail;
    data.create_success = store_io_stats.create.success;
}