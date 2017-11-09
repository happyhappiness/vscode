static int input_consumed_signal(h2_mplx *m, h2_stream *stream)
{
    if (stream->input) {
        return h2_beam_report_consumption(stream->input);
    }
    return 0;
}