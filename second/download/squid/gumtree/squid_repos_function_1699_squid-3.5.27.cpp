void
DelayPools::FreePools()
{
    if (!DelayPools::pools())
        return;

    FreeDelayData();
}