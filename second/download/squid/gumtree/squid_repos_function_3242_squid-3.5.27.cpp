static void
fqdncacheFreeEntry(void *data)
{
    fqdncache_entry *f = (fqdncache_entry *)data;
    int k;

    for (k = 0; k < (int) f->name_count; ++k)
        safe_free(f->names[k]);

    safe_free(f->hash.key);

    safe_free(f->error_message);

    memFree(f, MEM_FQDNCACHE_ENTRY);
}