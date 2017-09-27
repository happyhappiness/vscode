                     "write pipe_of_death");
    }

    return rv;
}

/* This function connects to the server and sends enough data to
 * ensure the child wakes up and processes a new connection.  This
 * permits the MPM to skip the poll when there is only one listening
 * socket, because it provides a alternate way to unblock an accept()
 * when the pod is used.  */
static apr_status_t dummy_connection(ap_pod_t *pod)
