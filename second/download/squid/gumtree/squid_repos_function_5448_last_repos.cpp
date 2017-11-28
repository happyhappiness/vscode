void checkHighWater() {
        if (hwater_level < level) {
            hwater_level = level;
            hwater_stamp = squid_curtime ? squid_curtime : time(NULL);
        }
    }