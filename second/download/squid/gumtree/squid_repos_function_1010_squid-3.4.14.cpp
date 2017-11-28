static const char *
ctx_get_descr(Ctx ctx)
{
    if (ctx < 0 || ctx > CTX_MAX_LEVEL)
        return "<lost>";

    return Ctx_Descrs[ctx] ? Ctx_Descrs[ctx] : "<null>";
}