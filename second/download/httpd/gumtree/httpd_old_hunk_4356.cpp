{
    if (beam && APLOG_C_IS_LEVEL(c,level)) {
        char buffer[2048];
        apr_size_t off = 0;
        
        off += apr_snprintf(buffer+off, H2_ALEN(buffer)-off, "cl=%d, ", beam->closed);
        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "red", ", ", &beam->red);
        off += h2_util_bb_print(buffer+off, H2_ALEN(buffer)-off, "green", ", ", beam->green);
        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "hold", ", ", &beam->hold);
        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "purge", "", &beam->purge);

        ap_log_cerror(APLOG_MARK, level, 0, c, "beam(%ld-%d): %s %s", 
                      c->id, id, msg, buffer);
    }
}

