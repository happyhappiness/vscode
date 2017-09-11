    }

    reply = (redisReply*)_reply;

    /* Check if we need to connect to a different node and reissue the request. */
    if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
        (!strncmp(reply->str,"MOVED",5) || !strcmp(reply->str,"ASK")))
    {
        char *p = reply->str, *s;
        int slot;

        output = 0;
        /* Comments show the position of the pointer as:
         *
         * [S] for pointer 's'
         * [P] for pointer 'p'
         */
        s = strchr(p,' ');      /* MOVED[S]3999 127.0.0.1:6381 */
        p = strchr(s+1,' ');    /* MOVED[S]3999[P]127.0.0.1:6381 */
        *p = '\0';
        slot = atoi(s+1);
        s = strchr(p+1,':');    /* MOVED 3999[P]127.0.0.1[S]6381 */
        *s = '\0';
        sdsfree(config.hostip);
        config.hostip = sdsnew(p+1);
        config.hostport = atoi(s+1);
        if (config.interactive)
            printf("-> Redirected to slot [%d] located at %s:%d\n",
                slot, config.hostip, config.hostport);
        config.cluster_reissue_command = 1;
    }

    if (output) {
        if (output_raw_strings) {
            out = cliFormatReplyRaw(reply);
        } else {
            if (config.raw_output) {
                out = cliFormatReplyRaw(reply);
                out = sdscat(out,"\n");
            } else {
                out = cliFormatReplyTTY(reply,"");
            }
        }
        fwrite(out,sdslen(out),1,stdout);
        sdsfree(out);
    }
    freeReplyObject(reply);
    return REDIS_OK;
}
