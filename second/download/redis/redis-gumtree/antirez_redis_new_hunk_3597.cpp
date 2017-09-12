    return mst;
}

/*------------------------------------------------------------------------------
 * Networking / parsing
 *--------------------------------------------------------------------------- */

/* Send AUTH command to the server */
static int cliAuth() {
    redisReply *reply;
    if (config.auth == NULL) return REDIS_OK;

    reply = redisCommand(context,"AUTH %s",config.auth);
    if (reply != NULL) {
        freeReplyObject(reply);
        return REDIS_OK;
    }
    return REDIS_ERR;
}

/* Send SELECT dbnum to the server */
static int cliSelect() {
    redisReply *reply;
    char dbnum[16];
    if (config.dbnum == 0) return REDIS_OK;

    snprintf(dbnum,sizeof(dbnum),"%d",config.dbnum);
    reply = redisCommand(context,"SELECT %s",dbnum);
    if (reply != NULL) {
        freeReplyObject(reply);
        return REDIS_OK;
    }
    return REDIS_ERR;
}

/* Connect to the client. If force is not zero the connection is performed
 * even if there is already a connected socket. */
static int cliConnect(int force) {
    if (context == NULL || force) {
        if (context != NULL)
            redisFree(context);

        if (config.hostsocket == NULL) {
            context = redisConnect(config.hostip,config.hostport);
        } else {
            context = redisConnectUnix(config.hostsocket);
        }

        if (context->err) {
            fprintf(stderr,"Could not connect to Redis at ");
            if (config.hostsocket == NULL)
                fprintf(stderr,"%s:%d: %s\n",config.hostip,config.hostport,context->errstr);
            else
                fprintf(stderr,"%s: %s\n",config.hostsocket,context->errstr);
            redisFree(context);
            context = NULL;
            return REDIS_ERR;
        }

        /* Do AUTH and select the right DB. */
        if (cliAuth() != REDIS_OK)
            return REDIS_ERR;
        if (cliSelect() != REDIS_OK)
            return REDIS_ERR;
    }
    return REDIS_OK;
}

static void cliPrintContextErrorAndExit() {
    if (context == NULL) return;
    fprintf(stderr,"Error: %s\n",context->errstr);
    exit(1);
}

static sds cliFormatReply(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        out = sdscat(out,prefix);
        if (config.tty) out = sdscat(out,"(error) ");
        out = sdscatprintf(out,"%s\n", r->str);
    break;
    case REDIS_REPLY_STATUS:
        out = sdscat(out,prefix);
        out = sdscat(out,r->str);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_INTEGER:
        out = sdscat(out,prefix);
        if (config.tty) out = sdscat(out,"(integer) ");
        out = sdscatprintf(out,"%lld\n",r->integer);
    break;
    case REDIS_REPLY_STRING:
        out = sdscat(out,prefix);
        if (config.raw_output || !config.tty) {
            out = sdscatlen(out,r->str,r->len);
        } else {
            /* If you are producing output for the standard output we want
             * a more interesting output with quoted characters and so forth */
            out = sdscatrepr(out,r->str,r->len);
            out = sdscat(out,"\n");
        }
    break;
    case REDIS_REPLY_NIL:
        out = sdscat(out,prefix);
        out = sdscat(out,"(nil)\n");
    break;
    case REDIS_REPLY_ARRAY:
        if (r->elements == 0) {
            out = sdscat(out,prefix);
            out = sdscat(out,"(empty list or set)\n");
        } else {
            unsigned int i;
            sds tmp;

            for (i = 0; i < r->elements; i++) {
                tmp = cliFormatReply(r->element[i],prefix);
                out = sdscat(out,prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);
            }
        }
    break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}

static int cliReadReply() {
    redisReply *reply;
    sds out;

    if (redisGetReply(context,(void**)&reply) != REDIS_OK) {
        if (config.shutdown)
            return REDIS_OK;
        if (config.interactive) {
            /* Filter cases where we should reconnect */
            if (context->err == REDIS_ERR_IO && errno == ECONNRESET)
                return REDIS_ERR;
            if (context->err == REDIS_ERR_EOF)
                return REDIS_ERR;
        }
        cliPrintContextErrorAndExit();
        return REDIS_ERR; /* avoid compiler warning */
    }

    out = cliFormatReply(reply,"");
    freeReplyObject(reply);
    fwrite(out,sdslen(out),1,stdout);
    sdsfree(out);
    return REDIS_OK;
}

static void showInteractiveHelp(void) {
