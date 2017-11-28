void
DelayPools::Update(void *unused)
{
    if (!pools())
        return;

    eventAdd("DelayPools::Update", Update, NULL, 1.0, 1);

    int incr = squid_curtime - LastUpdate;

    if (incr < 1)
        return;

    LastUpdate = squid_curtime;

    std::vector<Updateable *>::iterator pos = toUpdate.begin();

    while (pos != toUpdate.end()) {
        (*pos)->update(incr);
        ++pos;
    }
}