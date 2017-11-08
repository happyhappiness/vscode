static const char *remove_extension_type(cmd_parms *cmd, void *m_,
                                         const char *ext)
{
    return add_extension_info(cmd, m_, "", ext);
}