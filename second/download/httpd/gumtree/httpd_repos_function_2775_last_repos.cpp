void h2_beam_mutex_enable(h2_bucket_beam *beam)
{
    h2_beam_mutex_set(beam, mutex_enter, beam);
}