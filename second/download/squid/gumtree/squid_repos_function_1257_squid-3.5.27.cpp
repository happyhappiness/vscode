static void
memBufStats(std::ostream & stream)
{
    stream << "Large buffers: " <<
           HugeBufCountMeter.level << " (" <<
           HugeBufVolumeMeter.level / 1024 << " KB)\n";
}