    if(server.masterauth) {
        err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
        if (err[0] == '-') {
            serverLog(LL_WARNING,"Unable to AUTH to MASTER: %s",err);
            sdsfree(err);
            goto error;
        }
