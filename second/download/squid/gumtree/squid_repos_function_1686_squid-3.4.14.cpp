void
httpHdrScCleanModule(void)
{
    httpHeaderDestroyFieldsInfo(ScFieldsInfo, SC_ENUM_END);
    ScFieldsInfo = NULL;
}