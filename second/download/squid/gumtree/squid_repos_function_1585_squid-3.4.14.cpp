void
DelayPools::InitDelayData()
{
    if (!pools())
        return;

    DelayPools::delay_data = new DelayPool[pools()];

    DelayPools::MemoryUsed += pools() * sizeof(DelayPool);

    eventAdd("DelayPools::Update", DelayPools::Update, NULL, 1.0, 1);
}