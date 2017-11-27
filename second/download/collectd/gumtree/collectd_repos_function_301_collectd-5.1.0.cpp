static char *camqp_strerror (camqp_config_t *conf, /* {{{ */
        char *buffer, size_t buffer_size)
{
    amqp_rpc_reply_t r;

    r = amqp_get_rpc_reply (conf->connection);
    switch (r.reply_type)
    {
        case AMQP_RESPONSE_NORMAL:
            sstrncpy (buffer, "Success", sizeof (buffer));
            break;

        case AMQP_RESPONSE_NONE:
            sstrncpy (buffer, "Missing RPC reply type", sizeof (buffer));
            break;

        case AMQP_RESPONSE_LIBRARY_EXCEPTION:
#if HAVE_AMQP_RPC_REPLY_T_LIBRARY_ERRNO
            if (r.library_errno)
                return (sstrerror (r.library_errno, buffer, buffer_size));
#else
            if (r.library_error)
                return (sstrerror (r.library_error, buffer, buffer_size));
#endif
            else
                sstrncpy (buffer, "End of stream", sizeof (buffer));
            break;

        case AMQP_RESPONSE_SERVER_EXCEPTION:
            if (r.reply.id == AMQP_CONNECTION_CLOSE_METHOD)
            {
                amqp_connection_close_t *m = r.reply.decoded;
                char *tmp = camqp_bytes_cstring (&m->reply_text);
                ssnprintf (buffer, buffer_size, "Server connection error %d: %s",
                        m->reply_code, tmp);
                sfree (tmp);
            }
            else if (r.reply.id == AMQP_CHANNEL_CLOSE_METHOD)
            {
                amqp_channel_close_t *m = r.reply.decoded;
                char *tmp = camqp_bytes_cstring (&m->reply_text);
                ssnprintf (buffer, buffer_size, "Server channel error %d: %s",
                        m->reply_code, tmp);
                sfree (tmp);
            }
            else
            {
                ssnprintf (buffer, buffer_size, "Server error method %#"PRIx32,
                        r.reply.id);
            }
            break;

        default:
            ssnprintf (buffer, buffer_size, "Unknown reply type %i",
                    (int) r.reply_type);
    }

    return (buffer);
}