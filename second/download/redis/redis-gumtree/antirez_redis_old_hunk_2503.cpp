    /* Delete the key */
    server.stat_expiredkeys++;
    propagateExpire(db,key);
    return dbDelete(db,key);
}

