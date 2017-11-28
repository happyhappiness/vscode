void
IpcIoFile::configure(const Config &cfg)
{
    DiskFile::configure(cfg);
    config = cfg;
}