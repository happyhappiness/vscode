void
ctx_exit(Ctx ctx)
{
    assert(ctx >= 0);
    Ctx_Current_Level = (ctx >= 0) ? ctx - 1 : -1;

    if (Ctx_Valid_Level > Ctx_Current_Level)
        Ctx_Valid_Level = Ctx_Current_Level;
}