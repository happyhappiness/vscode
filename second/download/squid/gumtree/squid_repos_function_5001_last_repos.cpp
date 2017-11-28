void
Rock::Rebuild::checkpoint()
{
    if (!done())
        eventAdd("Rock::Rebuild", Rock::Rebuild::Steps, this, 0.01, 1, true);
}