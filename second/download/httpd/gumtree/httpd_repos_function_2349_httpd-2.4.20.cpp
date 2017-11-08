static int io_in_consumed_signal(h2_mplx *m, h2_io *io)
{
    if (io->input_consumed && m->input_consumed) {
        m->input_consumed(m->input_consumed_ctx, 
                          io->id, io->input_consumed);
        io->input_consumed = 0;
        return 1;
    }
    return 0;
}