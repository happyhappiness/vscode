void
httpHdrCcInitModule(void)
{
    CcFieldsInfo = httpHeaderBuildFieldsInfo(CcAttrs, CC_ENUM_END);
}