static void
cbdataInternalInitType(cbdata_type type, const char *name, int size)
{
    char *label;
    assert (type == cbdata_types + 1);

    cbdata_index = (CBDataIndex *)xrealloc(cbdata_index, (type + 1) * sizeof(*cbdata_index));
    memset(&cbdata_index[type], 0, sizeof(*cbdata_index));
    cbdata_types = type;

    label = (char *)xmalloc(strlen(name) + 20);

    snprintf(label, strlen(name) + 20, "cbdata %s (%d)", name, (int) type);

#if !WITH_VALGRIND
    assert((size_t)cbdata::Offset == (sizeof(cbdata) - ((cbdata *)NULL)->dataSize()));
    size += cbdata::Offset;
#endif

    cbdata_index[type].pool = memPoolCreate(label, size);
}