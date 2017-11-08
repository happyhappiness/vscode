static int io_out_consumed_signal(h2_mplx *m, h2_io *io)
{
    if (io->output_consumed && io->task && io->task->assigned) {
        h2_req_engine_out_consumed(io->task->assigned, io->task->c, 
                                   io->output_consumed);
        io->output_consumed = 0;
        return 1;
    }
    return 0;
}