    /* Return when this key has not expired */
    if (now <= when) return 0;

    /* Delete the key */
    server.stat_expiredkeys++;
    propagateExpire(db,key);
    notifyKeyspaceEvent(NOTIFY_EXPIRED,
        "expired",key,db->id);
    return dbDelete(db,key);
}

/*-----------------------------------------------------------------------------
 * Expires Commands
