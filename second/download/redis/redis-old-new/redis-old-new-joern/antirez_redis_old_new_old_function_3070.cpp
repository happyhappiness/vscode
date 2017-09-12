void *dsRdbSave_thread(void *arg) {
    char tmpfile[256], *filename = (char*)arg;
    struct dirent *dp, de;
    int j, i, last_dbid = -1;
    FILE *fp;

    /* Change state to ACTIVE, to signal there is a saving thead working. */
    redisLog(REDIS_NOTICE,"Diskstore BGSAVE thread started");
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_ACTIVE);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
        return NULL;
    }
    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;

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
                /* If there is a '-' char in the file name, it's a temp file */
                if (strchr(dp->d_name,'-') != NULL) continue;

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
    fsync(fileno(fp));
    fclose(fp);
    zfree(filename);

    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) {
        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
        return NULL;
    }
    redisLog(REDIS_NOTICE,"DB saved on disk by diskstore thread");
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_OK);
    return NULL;

werr:
    zfree(filename);
    fclose(fp);
    unlink(tmpfile);
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
    return NULL;
}