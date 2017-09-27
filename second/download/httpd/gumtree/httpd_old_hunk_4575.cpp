            return h2_config_get_priority(stream->session->config, ctype);
        }
    }
    return NULL;
}

const char *h2_stream_state_str(h2_stream *stream)
{
    switch (stream->state) {
        case H2_STREAM_ST_IDLE:
            return "IDLE";
        case H2_STREAM_ST_OPEN:
            return "OPEN";
        case H2_STREAM_ST_RESV_LOCAL:
            return "RESERVED_LOCAL";
        case H2_STREAM_ST_RESV_REMOTE:
            return "RESERVED_REMOTE";
        case H2_STREAM_ST_CLOSED_INPUT:
            return "HALF_CLOSED_REMOTE";
        case H2_STREAM_ST_CLOSED_OUTPUT:
            return "HALF_CLOSED_LOCAL";
        case H2_STREAM_ST_CLOSED:
            return "CLOSED";
        default:
            return "UNKNOWN";
            
    }
}

int h2_stream_is_ready(h2_stream *stream)
{
    if (stream->has_response) {
        return 1;
    }
    else if (stream->out_buffer && get_first_headers_bucket(stream->out_buffer)) {
        return 1;
    }
    return 0;
}


