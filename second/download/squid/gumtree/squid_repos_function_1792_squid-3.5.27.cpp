void
httpHdrScInitModule(void)
{
    ScFieldsInfo = httpHeaderBuildFieldsInfo(ScAttrs, SC_ENUM_END);
}