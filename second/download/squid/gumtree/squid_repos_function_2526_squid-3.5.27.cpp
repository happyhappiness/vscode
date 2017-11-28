void
httpHdrCcInitModule(void)
{
    /* build lookup and accounting structures */
    for (int32_t i = 0; i < CC_ENUM_END; ++i) {
        const HttpHeaderCcFields &f=CcAttrs[i];
        assert(i == f.id); /* verify assumption: the id is the key into the array */
        const SBuf k(f.name);
        CcNameToIdMap[k]=f.id;
    }
}