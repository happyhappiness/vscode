        addReplyBulkCString(c,"overhead.total");
        addReplyLongLong(c,mh->overhead_total);

        addReplyBulkCString(c,"dataset");
        addReplyLongLong(c,mh->dataset);

        freeMemoryOverheadData(mh);
    } else {
        addReplyError(c,"Syntax error. Try MEMORY [usage <key>] | [overhead]");
    }
}
