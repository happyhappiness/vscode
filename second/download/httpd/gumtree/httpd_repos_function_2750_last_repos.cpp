static void leave_yellow(h2_bucket_beam *beam, h2_beam_lock *pbl)
{
    if (pbl->leave) {
        pbl->leave(pbl->leave_ctx, pbl->mutex);
    }
}