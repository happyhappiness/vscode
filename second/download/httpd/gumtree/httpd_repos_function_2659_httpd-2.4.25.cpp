static void report_consumption(h2_bucket_beam *beam, int force)
{
    if (force || beam->received_bytes != beam->reported_consumed_bytes) {
        if (beam->consumed_fn) { 
            beam->consumed_fn(beam->consumed_ctx, beam, beam->received_bytes
                              - beam->reported_consumed_bytes);
        }
        beam->reported_consumed_bytes = beam->received_bytes;
    }
}