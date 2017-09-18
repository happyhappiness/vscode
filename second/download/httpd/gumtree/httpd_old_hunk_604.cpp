    else if (status != APR_SUCCESS) {
        err_except++; /* XXX: is this the right error counter? */
        /* XXX: Should errors here be fatal, or should we allow a
         * certain number of them before completely failing? -aaron */
        apr_err("apr_recv", status);
    }

    totalread += r;
    if (c->read == 0) {
	c->beginread = apr_time_now();
    }
    c->read += r;
