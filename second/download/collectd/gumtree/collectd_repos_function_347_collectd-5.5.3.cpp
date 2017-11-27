static int camqp_read_header (camqp_config_t *conf) /* {{{ */
{
    int status;
    amqp_frame_t frame;
    amqp_basic_properties_t *properties;
    char *content_type;

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

    if (frame.frame_type != AMQP_FRAME_HEADER)
    {
        NOTICE ("amqp plugin: Unexpected frame type: %#"PRIx8,
                frame.frame_type);
        return (-1);
    }

    properties = frame.payload.properties.decoded;
    content_type = camqp_bytes_cstring (&properties->content_type);
    if (content_type == NULL)
    {
        ERROR ("amqp plugin: Unable to determine content type.");
        return (-1);
    }

    status = camqp_read_body (conf,
            (size_t) frame.payload.properties.body_size,
            content_type);

    sfree (content_type);
    return (status);
}