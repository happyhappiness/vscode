        apr_socket_close(lr->sd);
        lr->active = 0;
        next = lr->next;
    }
    old_listeners = NULL;

    apr_pool_cleanup_register(pool, NULL, apr_pool_cleanup_null,
                              close_listeners_on_exec);

    return num_open ? 0 : -1;
}

int ap_setup_listeners(server_rec *s)
{
