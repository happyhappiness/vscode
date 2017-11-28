
        Ctx_Reported_Level = Ctx_Valid_Level;
    }

    /* report new contexts that were pushed since last report */
    while (Ctx_Reported_Level < Ctx_Current_Level) {
        Ctx_Reported_Level++;
        Ctx_Valid_Level++;
        _db_print("ctx: enter level %2d: '%s'\n", Ctx_Reported_Level,
                  ctx_get_descr(Ctx_Reported_Level));
    }

    /* unlock */
    Ctx_Lock--;
}

/* checks for nulls and overflows */
static const char *
ctx_get_descr(Ctx ctx)
{
