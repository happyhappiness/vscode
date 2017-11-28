
    if (!xstrtoui(token, NULL, &mark, 0, std::numeric_limits<nfmark_t>::max())) {
        self_destruct();
        return;
    }

    acl_nfmark *l = new acl_nfmark;

    l->nfmark = mark;

    aclParseAclList(LegacyParser, &l->aclList, token);

    acl_nfmark **tail = head;   /* sane name below */
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_nfmark(acl_nfmark ** head)
{
    delete *head;
    *head = NULL;
}
#endif /* SO_MARK */

static void
dump_acl_b_size_t(StoreEntry * entry, const char *name, AclSizeLimit * head)
{
    for (AclSizeLimit *l = head; l; l = l->next) {
        if (l->size != -1)
            storeAppendPrintf(entry, "%s %d %s\n", name, (int) l->size, B_BYTES_STR);
        else
            storeAppendPrintf(entry, "%s none", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
parse_acl_b_size_t(AclSizeLimit ** head)
{
    AclSizeLimit *l = new AclSizeLimit;

    parse_b_int64_t(&l->size);

    aclParseAclList(LegacyParser, &l->aclList, l->size);

    AclSizeLimit **tail = head; /* sane name below */
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_b_size_t(AclSizeLimit ** head)
{
    delete *head;
    *head = NULL;
}

#if USE_DELAY_POOLS

#include "DelayConfig.h"
#include "DelayPools.h"
