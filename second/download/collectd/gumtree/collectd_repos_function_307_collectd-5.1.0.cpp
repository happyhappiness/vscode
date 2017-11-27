static int camqp_read_body (camqp_config_t *conf, /* {{{ */
        size_t body_size, const char *content_type)
{
    char body[body_size + 1];
    char *body_ptr;
    size_t received;
    amqp_frame_t frame;
    int status;

    memset (body, 0, sizeof (body));
    body_ptr = &body[0];
    received = 0;

    while (received < body_size)
    {
        status = amqp_simple_wait_frame (conf->connection, &frame);
        if (status < 0)
        {
            char errbuf[1024];
            status = (-1) * status;
            ERROR ("amqp plugin: amqp_simple_wait_frame failed: %s",
                    sstrerror (status, errbuf, sizeof (errbuf)));
            camqp_close_connection (conf);
            return (status);
        }

        if (frame.frame_type != AMQP_FRAME_BODY)
        {
            NOTICE ("amqp plugin: Unexpected frame type: %#"PRIx8,
                    frame.frame_type);
            return (-1);
        }

        if ((body_size - received) < frame.payload.body_fragment.len)
        {
            WARNING ("amqp plugin: Body is larger than indicated by header.");
            return (-1);
        }

        memcpy (body_ptr, frame.payload.body_fragment.bytes,
                frame.payload.body_fragment.len);
        body_ptr += frame.payload.body_fragment.len;
        received += frame.payload.body_fragment.len;
    } /* while (received < body_size) */

    if (strcasecmp ("text/collectd", content_type) == 0)
    {
        status = handle_putval (stderr, body);
        if (status != 0)
            ERROR ("amqp plugin: handle_putval failed with status %i.",
                    status);
        return (status);
    }
    else if (strcasecmp ("application/json", content_type) == 0)
    {
        ERROR ("amqp plugin: camqp_read_body: Parsing JSON data has not "
                "been implemented yet. FIXME!");
        return (0);
    }
    else
    {
        ERROR ("amqp plugin: camqp_read_body: Unknown content type \"%s\".",
                content_type);
        return (EINVAL);
    }

    /* not reached */
    return (0);
}