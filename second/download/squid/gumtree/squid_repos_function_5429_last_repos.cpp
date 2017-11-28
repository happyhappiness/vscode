void
Mem::CleanIdlePools(void *)
{
    MemPools::GetInstance().clean(static_cast<time_t>(clean_interval));
    eventAdd("memPoolCleanIdlePools", CleanIdlePools, NULL, clean_interval, 1);
}