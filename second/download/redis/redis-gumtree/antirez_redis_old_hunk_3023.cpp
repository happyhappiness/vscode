    }

    reply = (redisReply*)_reply;
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
    freeReplyObject(reply);
    return REDIS_OK;
}
