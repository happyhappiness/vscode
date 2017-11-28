void
DelayPools::FreeDelayData()
{
    eventDelete(DelayPools::Update, NULL);
    delete[] DelayPools::delay_data;
    DelayPools::MemoryUsed -= pools() * sizeof(*DelayPools::delay_data);
    pools_ = 0;
}