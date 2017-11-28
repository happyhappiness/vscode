static void
fqdncacheHandleReply(void *data, const rfc1035_rr * answers, int na, const char *error_message)
{
    fqdncache_entry *f;
    static_cast<generic_cbdata *>(data)->unwrap(&f);
    ++FqdncacheStats.replies;
    const int age = f->age();
    statCounter.dns.svcTime.count(age);
    fqdncacheParse(f, answers, na, error_message);
    fqdncacheAddEntry(f);
    fqdncacheCallback(f, age);
}