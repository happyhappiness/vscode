static void
memBufStats(std::ostream & stream)
{
    stream << "Large buffers: " <<
           HugeBufCountMeter.currentLevel() << " (" <<
           HugeBufVolumeMeter.currentLevel() / 1024 << " KB)\n";
}