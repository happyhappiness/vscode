static void
fqdncacheLockEntry(fqdncache_entry * f)
{
    if (f->locks++ == 0) {
        dlinkDelete(&f->lru, &lru_list);
        dlinkAdd(f, &f->lru, &lru_list);
    }
}