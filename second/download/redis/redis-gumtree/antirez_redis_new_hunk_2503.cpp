    /* Delete the key */
    server.stat_expiredkeys++;
    propagateExpire(db,key);
    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
        "expired",key,db->id);
    return dbDelete(db,key);
}

