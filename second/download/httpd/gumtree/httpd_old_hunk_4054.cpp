    }
    return status;
}

apr_table_t *h2_stream_get_trailers(h2_stream *stream)
{
    return stream->response? stream->response->trailers : NULL;
}

const h2_priority *h2_stream_get_priority(h2_stream *stream)
{
    if (stream->initiated_on && stream->response) {
        const char *ctype = apr_table_get(stream->response->headers, "content-type");
        if (ctype) {
            /* FIXME: Not good enough, config needs to come from request->server */
            return h2_config_get_priority(stream->session->config, ctype);
        }
    }
    return NULL;
}

