{
    return new DiskdIOStrategy();
}

DiskDaemonDiskIOModule DiskDaemonDiskIOModule::Instance;

char const *
DiskDaemonDiskIOModule::type () const
{
    return "DiskDaemon";
}
