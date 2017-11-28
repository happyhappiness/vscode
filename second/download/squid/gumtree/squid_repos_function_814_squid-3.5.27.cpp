void FadingCounter::clear()
{
    for (int i = 0; i < precision; ++i)
        counters[i] = 0;
    lastTime = current_dtime;
    total = 0;
}