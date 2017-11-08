int h2_io_in_has_eos_for(h2_io *io)
{
    return io->eos_in || (io->bbin && h2_util_has_eos(io->bbin, 0));
}