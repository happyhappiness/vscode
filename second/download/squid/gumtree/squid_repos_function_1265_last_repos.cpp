void
DelayPools::InitDelayData()
{
    if (!pools())
        return;

    DelayPools::delay_data = new DelayPool[pools()];

    eventAdd("DelayPools::Update", DelayPools::Update, NULL, 1.0, 1);
}