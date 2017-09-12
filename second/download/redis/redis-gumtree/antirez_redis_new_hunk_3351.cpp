
    sleep(5);

    /* Scan all diskstore dirs looking for keys */
    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            DIR *dir;
            char buf[1024];

            /* For every directory, collect all the keys */
            snprintf(buf,sizeof(buf),"%s/%02x/%02x",server.ds_path,j,i);
            if ((dir = opendir(buf)) == NULL) {
                redisLog(REDIS_WARNING,"Disk store can't open dir %s: %s",
                    buf, strerror(errno));
                goto werr;
            }

            while(1) {
                char buf[1024];
                int dbid;
                FILE *entryfp;

                readdir_r(dir,&de,&dp);
                if (dp == NULL) break;
                if (dp->d_name[0] == '.') continue;

                /* Emit the SELECT DB opcode if needed. */
                dbid = dsGetDbidFromFilename(dp->d_name);
                if (dbid != last_dbid) {
                    last_dbid = dbid;
                    if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
                    if (rdbSaveLen(fp,dbid) == -1) goto werr;
                }

                /* Let's copy this file into the target .rdb */
                snprintf(buf,sizeof(buf),"%s/%02x/%02x/%s",
                    server.ds_path,j,i,dp->d_name);
                if ((entryfp = fopen(buf,"r")) == NULL) {
                    redisLog(REDIS_WARNING,"Can't open %s: %s",
                        buf,strerror(errno));
                    closedir(dir);
                    goto werr;
                }
                while(1) {
                    int nread = fread(buf,1,sizeof(buf),entryfp);

                    if (nread == 0) {
                        if (ferror(entryfp)) {
                            redisLog(REDIS_WARNING,"Error reading from file entry while performing BGSAVE for diskstore: %s", strerror(errno));
                            closedir(dir);
                            goto werr;
                        } else {
                            break;
                        }
                    }
                    if (fwrite(buf,1,nread,fp) != (unsigned)nread) {
                        closedir(dir);
                        goto werr;
                    }
                }
                fclose(entryfp);
            }
            closedir(dir);
        }
    }
    
    /* Output the end of file opcode */
    if (rdbSaveType(fp,REDIS_EOF) == -1) goto werr;

    /* Make sure data will not remain on the OS's output buffers */
    fflush(fp);
