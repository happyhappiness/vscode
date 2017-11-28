bool
Mgr::StoreToCommWriter::doneAll() const
{
    return entry &&
           entry->store_status == STORE_OK && // the action is over
           writeOffset >= entry->objectLen(); // we wrote all the results
}