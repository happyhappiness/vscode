    sds ci;

    /* Node coordinates */
    ci = sdscatprintf(sdsempty(),"%.40s %s:%d@%d ",
        node->name,
        node->ip,
        node->port,
