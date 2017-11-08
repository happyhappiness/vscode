static const char *get_sos_filter(apr_table_t *notes) 
{
    return notes? apr_table_get(notes, H2_RESP_SOS_NOTE) : NULL;
}