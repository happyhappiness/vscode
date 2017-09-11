                addReplyError(c,"Unable to perform background save");
                return;
            }
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
            replicationSendFullresyncReply(c,getPsyncInitialOffset());
        }
    }

    if (server.repl_disable_tcp_nodelay)
        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
    c->repldbfd = -1;
    c->flags |= CLIENT_SLAVE;
    server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
    listAddNodeTail(server.slaves,c);
    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
        createReplicationBacklog();
