                fprintf(stderr, "Completed %d requests\n", done);
                fflush(stderr);
            }
        }
    }

    set_conn_state(c, STATE_UNCONNECTED);
#ifdef USE_SSL
    if (c->ssl) {
        SSL_shutdown(c->ssl);
        SSL_free(c->ssl);
        c->ssl = NULL;
    }
#endif
    apr_socket_close(c->aprsock);

    /* connect again */
    start_connect(c);
    return;
}

