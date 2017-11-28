bool Adaptation::Icap::ModXact::virginBodyEndReached(const Adaptation::Icap::VirginBodyAct &act) const
{
    return
        !act.active() || // did all (assuming it was originally planned)
        !virgin.body_pipe->expectMoreAfter(act.offset()); // wont have more
}