        if (dp->d_name[0] == '.') continue;

        /* Check if we need to remove this entry accordingly to the
         * DB number. */
        if (dbid != -1 && dsGetDbidFromFilename(dp->d_name)) continue;
        
        /* Finally unlink the file */
        snprintf(buf,1024,"%s/%s",path,dp->d_name);
