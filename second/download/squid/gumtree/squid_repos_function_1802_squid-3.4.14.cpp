void
StatHist::logInit(unsigned int capacity, double min, double max)
{
    init(capacity, Math::Log, Math::Exp, min, max);
}