static const char *
describeStatuses(const StoreEntry * entry)
{
    LOCAL_ARRAY(char, buf, 256);
    snprintf(buf, 256, "%-13s %-13s %-12s %-12s",
             storeStatusStr[entry->store_status],
             memStatusStr[entry->mem_status],
             swapStatusStr[entry->swap_status],
             pingStatusStr[entry->ping_status]);
    return buf;
}