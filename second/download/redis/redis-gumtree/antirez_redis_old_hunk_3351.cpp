
    sleep(5);

#if 0
    /* Scan all diskstore dirs looking for keys */
    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);

            /* Write the SELECT DB opcode */
            if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
            if (rdbSaveLen(fp,j) == -1) goto werr;
        }
    }
#endif

    /* Make sure data will not remain on the OS's output buffers */
    fflush(fp);
