snprintf(ptr, left, " librtmp/%d.%d%s",
             RTMP_LIB_VERSION >> 16, (RTMP_LIB_VERSION >> 8) & 0xff,
             suff)