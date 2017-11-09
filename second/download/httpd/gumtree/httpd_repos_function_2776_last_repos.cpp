void h2_beam_mutex_disable(h2_bucket_beam *beam)
{
    h2_beam_mutex_set(beam, NULL, NULL);
}