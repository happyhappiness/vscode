        usage += sdsAllocSize(c->argv[1]->ptr);
        usage += sizeof(dictEntry);
        addReplyLongLong(c,usage);
    } else {
        addReplyError(c,"Syntax error. Try MEMORY usage <key>");
    }
}
