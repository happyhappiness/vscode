static void
statCountersInit(StatCounters * C)
{
    assert(C);
    memset(C, 0, sizeof(*C));
    C->timestamp = current_time;
    statCountersInitSpecial(C);
}