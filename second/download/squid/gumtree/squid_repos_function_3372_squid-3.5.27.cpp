static void
DeleteIdleConnList(void *hashItem)
{
    delete reinterpret_cast<IdleConnList*>(hashItem);
}