Mgr::StoreIoActionData&
Mgr::StoreIoActionData::operator += (const StoreIoActionData& stats)
{
    create_calls += stats.create_calls;
    create_select_fail += stats.create_select_fail;
    create_create_fail += stats.create_create_fail;
    create_success += stats.create_success;

    return *this;
}