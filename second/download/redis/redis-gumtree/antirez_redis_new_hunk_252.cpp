    }
}

/* The memory command will eventually be a complete interface for the
 * memory introspection capabilities of Redis.
 *
 * Usage: MEMORY usage <key> */
void memoryCommand(client *c) {
    robj *o;

    if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc == 3) {
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        size_t usage = objectComputeSize(o,OBJ_COMPUTE_SIZE_DEF_SAMPLES);
        usage += sdsAllocSize(c->argv[1]->ptr);
        usage += sizeof(dictEntry);
        addReplyLongLong(c,usage);
    } else {
        addReplyError(c,"Syntax error. Try MEMORY usage <key>");
    }
}
