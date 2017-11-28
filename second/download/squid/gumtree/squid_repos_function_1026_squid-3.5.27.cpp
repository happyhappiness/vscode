Ctx
ctx_enter(const char *descr)
{
    ++Ctx_Current_Level;

    if (Ctx_Current_Level <= CTX_MAX_LEVEL)
        Ctx_Descrs[Ctx_Current_Level] = descr;

    if (Ctx_Current_Level == Ctx_Warn_Level) {
        debugs(0, DBG_CRITICAL, "# ctx: suspiciously deep (" << Ctx_Warn_Level << ") nesting:");
        Ctx_Warn_Level *= 2;
    }

    return Ctx_Current_Level;
}