static void
fqdncacheUnlockEntry(fqdncache_entry * f)
{
    assert(f->locks > 0);
    -- f->locks;

    if (fqdncacheExpiredEntry(f))
        fqdncacheRelease(f);
}