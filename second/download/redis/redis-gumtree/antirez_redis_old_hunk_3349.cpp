        if (dp->d_name[0] == '.') continue;

        /* Check if we need to remove this entry accordingly to the
         * DB number */
        if (dbid != -1) {
            char id[64];
            char *p = strchr(dp->d_name,'_');
            int len = (p - dp->d_name);

            redisAssert(p != NULL && len < 64);
            memcpy(id,dp->d_name,len);
            id[len] = '\0';
            if (atoi(id) != dbid) continue; /* skip this file */
        }
        
        /* Finally unlink the file */
        snprintf(buf,1024,"%s/%s",path,dp->d_name);
