static const char *set_dbm_slot(cmd_parms *cmd, void *offset,
                                const char *f, const char *t)
{
    if (!t || strcmp(t, "dbm"))
        return DECLINE_CMD;

    return ap_set_file_slot(cmd, offset, f);
}