                fprintf(stderr, "Completed %d requests\n", done);
                fflush(stderr);
            }
        }
    }

    {
        apr_pollfd_t remove_pollfd;
        remove_pollfd.desc_type = APR_POLL_SOCKET;
        remove_pollfd.desc.s = c->aprsock;
        apr_pollset_remove(readbits, &remove_pollfd);
#ifdef USE_SSL
        if (c->ssl) {
            SSL_shutdown(c->ssl);
            SSL_free(c->ssl);
            c->ssl = NULL;
        }
#endif
        apr_socket_close(c->aprsock);
    }
    c->state = STATE_UNCONNECTED;

    /* connect again */
    start_connect(c);
    return;
}

