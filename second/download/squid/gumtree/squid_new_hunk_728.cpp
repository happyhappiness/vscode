
    debugs(3, DBG_CRITICAL, "WARNING: Unknown bytes unit '" << unit << "'");

    return 0;
}

static void
dump_SBufList(StoreEntry * entry, const SBufList &words)
{
    for (SBufList::const_iterator i = words.begin(); i != words.end(); ++i) {
        entry->append(i->rawContent(), i->length());
        entry->append(" ",1);
    }
    entry->append("\n",1);
}

static void
dump_acl(StoreEntry * entry, const char *name, ACL * ae)
{
    while (ae != NULL) {
        debugs(3, 3, "dump_acl: " << name << " " << ae->name);
        storeAppendPrintf(entry, "%s %s %s %s ",
                          name,
                          ae->name,
                          ae->typeString(),
                          ae->flags.flagsStr());
        dump_SBufList(entry, ae->dump());
        ae = ae->next;
    }
}

static void
parse_acl(ACL ** ae)
