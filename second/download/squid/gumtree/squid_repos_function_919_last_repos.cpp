void
DelayBucket::init(DelaySpec const &rate)
{
    level() = (int) (((double)rate.max_bytes *
                      Config.Delay.initial) / 100);
}