/*RR*/{  0, 0, 0, 1, 0, 0, 0 },
/*CI*/{  1, 1, 0, 0, 1, 0, 0 },
/*CO*/{  1, 1, 0, 0, 0, 1, 0 },
/*CL*/{  1, 1, 0, 0, 1, 1, 1 },
};

static int set_state(h2_stream *stream, h2_stream_state_t state)
{
    int allowed = state_transition[state][stream->state];
    if (allowed) {
        stream->state = state;
        return 1;
