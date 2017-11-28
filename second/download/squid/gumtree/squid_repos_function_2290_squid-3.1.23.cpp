void
httpHdrCcCleanModule(void)
{
    httpHeaderDestroyFieldsInfo(CcFieldsInfo, CC_ENUM_END);
    CcFieldsInfo = NULL;
}