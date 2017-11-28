static StatHist *
newStatHist() {
    StatHist *stats = new StatHist;
    stats->logInit(100, 30.0, 128000.0);
    return stats;
}