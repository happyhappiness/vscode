void
DelayConfig::freePoolCount()
{
    DelayPools::FreePools();
    initial = 50;
}