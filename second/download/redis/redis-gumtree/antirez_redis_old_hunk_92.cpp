    size_t rss_bytes = resident - allocated;
    if(out_frag_bytes)
        *out_frag_bytes = frag_bytes;
    serverLog(LL_DEBUG, 
        "allocated=%zu, active=%zu, resident=%zu, frag=%.0f%% (%.0f%% rss), frag_bytes=%zu (%zu%% rss)", 
        allocated, active, resident, frag_pct, rss_pct, frag_bytes, rss_bytes);
    return frag_pct;
}
