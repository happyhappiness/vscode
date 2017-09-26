                 */
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            conn->worker->s->transferred += bufsiz;
            send_body = 1;
        }
    }

    /* read the response */
    conn->data = NULL;
    status = ajp_read_header(conn->sock, r, maxsize,
                             (ajp_msg_t **)&(conn->data));
