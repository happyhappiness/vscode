ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
        node->name,
        node->ip,
        node->port);