static apr_status_t r_wait_space(h2_bucket_beam *beam, apr_read_type_e block,
                                 h2_beam_lock *pbl, apr_size_t *premain) 
{
    *premain = calc_space_left(beam);
    while (!beam->aborted && *premain <= 0 
           && (block == APR_BLOCK_READ) && pbl->mutex) {
        apr_status_t status;
        report_prod_io(beam, 1, pbl);
        status = wait_cond(beam, pbl->mutex);
        if (APR_STATUS_IS_TIMEUP(status)) {
            return status;
        }
        r_purge_sent(beam);
        *premain = calc_space_left(beam);
    }
    return beam->aborted? APR_ECONNABORTED : APR_SUCCESS;
}