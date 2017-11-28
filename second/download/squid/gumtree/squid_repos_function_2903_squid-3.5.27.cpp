void noCache(const String &v) {
        setMask(CC_NO_CACHE,true);
        if (!v.size())
            return;
        // uses append for multi-line headers
        if (no_cache.size() > 0 && v.size() > 0)
            no_cache.append(",");
        no_cache.append(v);
    }