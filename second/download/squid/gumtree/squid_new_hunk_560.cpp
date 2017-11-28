            storeAppendPrintf(sentry, " %s", f->names[k]);

        storeAppendPrintf(sentry, "\n");
    }
}

/// \ingroup FQDNCacheInternal
static void
fqdncacheLockEntry(fqdncache_entry * f)
{
    if (f->locks++ == 0) {
        dlinkDelete(&f->lru, &lru_list);
