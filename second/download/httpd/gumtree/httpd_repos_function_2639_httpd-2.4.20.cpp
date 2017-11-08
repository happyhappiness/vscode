int h2_io_out_has_data(h2_io *io)
{
    return io->bbout && h2_util_bb_has_data_or_eos(io->bbout);
}