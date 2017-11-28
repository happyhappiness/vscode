void
StatHist::enumInit(unsigned int last_enum)
{
    init(last_enum + 3, Math::Null, Math::Null, -1.0, (2.0 + last_enum));
}