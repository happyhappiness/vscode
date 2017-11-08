static int io_stream_done(h2_mplx *m, h2_io *io, int rst_error) 
{
    /* Remove io from ready set, we will never submit it */
    h2_io_set_remove(m->ready_ios, io);
    if (io->task_done || h2_tq_remove(m->q, io->id)) {
        /* already finished or not even started yet */
        io_destroy(m, io, 1);
        return 0;
    }
    else {
        /* cleanup once task is done */
        io->orphaned = 1;
        if (rst_error) {
            h2_io_rst(io, rst_error);
        }
        return 1;
    }
}