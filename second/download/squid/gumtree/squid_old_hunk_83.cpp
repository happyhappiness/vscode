        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}

CBDATA_TYPE(acl_size_t);

static void
dump_acl_b_size_t(StoreEntry * entry, const char *name, acl_size_t * head)
{
    acl_size_t *l;
