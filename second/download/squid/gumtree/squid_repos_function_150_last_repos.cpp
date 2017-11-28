void
Ping::DisplayStats()
{
    if (Ping::Config.enable && stats.counted) {
        long mean = stats.sum / stats.counted;
        std::cerr << std::endl
                  << stats.counted << " requests, round-trip (secs) min/avg/max = "
                  << (stats.pMin/1000) << "." << (stats.pMin%1000)
                  << "/" << (mean/1000) << "." << (mean%1000)
                  << "/" << (stats.pMax/1000) << "." << (stats.pMax%1000)
                  << std::endl;
    }
}