void noCache(String &v) {
        setMask(CC_NO_CACHE,true);
        // uses append for multi-line headers
        if (no_cache.defined())
            no_cache.append(",");
        no_cache.append(v);
    }