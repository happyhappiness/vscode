static void check_tx_free(h2_mplx *m) 
{
    if (m->tx_handles_reserved > m->tx_chunk_size) {
        apr_size_t count = m->tx_handles_reserved - m->tx_chunk_size;
        m->tx_handles_reserved = m->tx_chunk_size;
        h2_workers_tx_free(m->workers, count);
    }
    else if (m->tx_handles_reserved 
             && (!m->stream_ios || h2_io_set_is_empty(m->stream_ios))) {
        h2_workers_tx_free(m->workers, m->tx_handles_reserved);
        m->tx_handles_reserved = 0;
    }
}