void
statHistEnumInit(StatHist * H, int last_enum)
{
    statHistInit(H, last_enum + 3, Null, Null, (double) -1, (double) (last_enum + 1 + 1));
}