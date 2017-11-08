static void report_production(h2_bucket_beam *beam, int force)
{
    if (force || beam->sent_bytes != beam->reported_produced_bytes) {
        if (beam->produced_fn) { 
            beam->produced_fn(beam->produced_ctx, beam, beam->sent_bytes
                              - beam->reported_produced_bytes);
        }
        beam->reported_produced_bytes = beam->sent_bytes;
    }
}