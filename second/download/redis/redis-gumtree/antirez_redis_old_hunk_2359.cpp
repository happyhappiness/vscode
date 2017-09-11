    } else {
        /* TCP client. */
        int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
        if (strchr(ip,':'))
            snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
        else
            snprintf(peerid,peerid_len,"%s:%d",ip,port);
        return (retval == -1) ? REDIS_ERR : REDIS_OK;
    }
}
