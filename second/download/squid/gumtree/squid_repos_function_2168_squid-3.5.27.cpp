static void
cbdataInternalInitType(cbdata_type type, const char *name, int size, FREE * free_func)
{
    char *label;
    assert (type == cbdata_types + 1);

    cbdata_index = (CBDataIndex *)xrealloc(cbdata_index, (type + 1) * sizeof(*cbdata_index));
    memset(&cbdata_index[type], 0, sizeof(*cbdata_index));
    cbdata_types = type;

    label = (char *)xmalloc(strlen(name) + 20);

    snprintf(label, strlen(name) + 20, "cbdata %s (%d)", name, (int) type);

#if !HASHED_CBDATA
    assert((size_t)cbdata::Offset == (sizeof(cbdata) - ((cbdata *)NULL)->dataSize()));
    size += cbdata::Offset;
#endif

    cbdata_index[type].pool = memPoolCreate(label, size);

    cbdata_index[type].free_func = free_func;

#if HASHED_CBDATA
    if (!cbdata_htable)
        cbdata_htable = hash_create(cbdata_cmp, 1 << 12, cbdata_hash);
#endif
}