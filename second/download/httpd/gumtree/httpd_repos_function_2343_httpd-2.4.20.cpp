static void check_tx_reservation(h2_mplx *m) 
{
    if (m->tx_handles_reserved == 0) {
        m->tx_handles_reserved += h2_workers_tx_reserve(m->workers, 
            H2MIN(m->tx_chunk_size, h2_io_set_size(m->stream_ios)));
    }
}