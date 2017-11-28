        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}

#if SO_MARK && USE_LIBCAP

CBDATA_TYPE(acl_nfmark);

static void
dump_acl_nfmark(StoreEntry * entry, const char *name, acl_nfmark * head)
{
    acl_nfmark *l;

    for (l = head; l; l = l->next) {
        if (l->nfmark > 0)
            storeAppendPrintf(entry, "%s 0x%02X", name, l->nfmark);
        else
            storeAppendPrintf(entry, "%s none", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
freed_acl_nfmark(void *data)
{
    acl_nfmark *l = static_cast<acl_nfmark *>(data);
    aclDestroyAclList(&l->aclList);
}

static void
parse_acl_nfmark(acl_nfmark ** head)
{
    acl_nfmark *l;
    acl_nfmark **tail = head;	/* sane name below */
    nfmark_t mark;
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    if (!xstrtoui(token, NULL, &mark, 0, std::numeric_limits<nfmark_t>::max())) {
        self_destruct();
        return;
    }

    CBDATA_INIT_TYPE_FREECB(acl_nfmark, freed_acl_nfmark);

    l = cbdataAlloc(acl_nfmark);

    l->nfmark = mark;

    aclParseAclList(LegacyParser, &l->aclList);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_nfmark(acl_nfmark ** head)
{
    while (*head) {
        acl_nfmark *l = *head;
        *head = l->next;
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
