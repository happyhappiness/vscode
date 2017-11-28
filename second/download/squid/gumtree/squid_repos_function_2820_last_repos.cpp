static void
DeleteIdleConnList(void *hashItem)
{
    delete static_cast<IdleConnList*>(hashItem);
}