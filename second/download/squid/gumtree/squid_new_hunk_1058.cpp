        if (node->children.concurrency != 0)
            storeAppendPrintf(sentry, " concurrency=%d", node->children.concurrency);

        if (node->cache)
            storeAppendPrintf(sentry, " cache=%d", node->cache_size);

        if (node->quote == Format::LOG_QUOTE_SHELL)
            storeAppendPrintf(sentry, " protocol=2.5");

        node->format.dump(sentry, NULL, false);

        for (word = node->cmdline; word; word = word->next)
            storeAppendPrintf(sentry, " %s", word->key);

        storeAppendPrintf(sentry, "\n");
    }
}

void
free_externalAclHelper(external_acl ** list)
{
    delete *list;
    *list = NULL;
}

static external_acl *
find_externalAclHelper(const char *name)
{
    external_acl *node;
