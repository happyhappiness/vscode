        l->next = NULL;
        cbdataFree(l);
    }
}
#endif /* SO_MARK */

CBDATA_TYPE(acl_size_t);

static void
dump_acl_b_size_t(StoreEntry * entry, const char *name, acl_size_t * head)
{
    acl_size_t *l;

    for (l = head; l; l = l->next) {
        if (l->size != -1)
            storeAppendPrintf(entry, "%s %d %s\n", name, (int) l->size, B_BYTES_STR);
        else
            storeAppendPrintf(entry, "%s none", name);
