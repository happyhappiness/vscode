                server.client_obuf_limits[j].soft_limit_bytes);

        line = sdscatprintf(sdsempty(),"%s %s %s %s %ld",
                option, getClientTypeName(j), hard, soft,
                (long) server.client_obuf_limits[j].soft_limit_seconds);
        rewriteConfigRewriteLine(state,option,line,force);
    }
