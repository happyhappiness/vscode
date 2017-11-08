static void input_consumed_signal(h2_mplx *m, h2_stream *stream)
{
    if (stream->input && stream->started) {
        h2_beam_send(stream->input, NULL, 0); /* trigger updates */
    }
}