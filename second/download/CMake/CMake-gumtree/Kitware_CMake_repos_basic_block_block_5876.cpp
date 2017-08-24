{
              foundPendingCandidate = TRUE;
              DEBUGF(infof(data,
                           "Connection #%ld has not started SSL connect, "
                           "can't reuse\n",
                           check->connection_id));
              continue;
            }