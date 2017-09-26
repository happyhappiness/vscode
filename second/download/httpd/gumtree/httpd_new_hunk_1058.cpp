
static void read_connection(struct connection * c)
{
    apr_size_t r;
    apr_status_t status;
    char *part;
    char respcode[4];       /* 3 digits and null */

    r = sizeof(buffer);
#ifdef USE_SSL
    if (c->ssl) {
        status = SSL_read(c->ssl, buffer, r);
        if (status <= 0) {
            int scode = SSL_get_error(c->ssl, status);

            if (scode == SSL_ERROR_ZERO_RETURN) {
                /* connection closed cleanly: */
                good++;
                close_connection(c);
            }
            else if (scode != SSL_ERROR_WANT_WRITE
                     && scode != SSL_ERROR_WANT_READ) {
                /* some fatal error: */
                c->read = 0;
                BIO_printf(bio_err, "SSL read failed - closing connection\n");
                ERR_print_errors(bio_err);
                close_connection(c);
            }
            return;
        }
        r = status;
    }
    else
#endif
    {
        status = apr_socket_recv(c->aprsock, buffer, &r);
        if (APR_STATUS_IS_EAGAIN(status))
            return;
        else if (r == 0 && APR_STATUS_IS_EOF(status)) {
            good++;
            close_connection(c);
            return;
        }
        /* catch legitimate fatal apr_socket_recv errors */
        else if (status != APR_SUCCESS) {
            err_except++; /* XXX: is this the right error counter? */
            /* XXX: Should errors here be fatal, or should we allow a
             * certain number of them before completely failing? -aaron */
            apr_err("apr_socket_recv", status);
        }
    }

    totalread += r;
    if (c->read == 0) {
	c->beginread = apr_time_now();
    }
    c->read += r;
