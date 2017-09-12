snprintf(slavename,sizeof(slavename),
            strchr(hostname,':') ? "[%s]:%d" : "%s:%d",
            hostname,port);