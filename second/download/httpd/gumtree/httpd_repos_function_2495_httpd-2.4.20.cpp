h2_sos *h2_filter_sos_create(const char *name, struct h2_sos *prev)
{
    if (!strcmp(H2_SOS_H2_STATUS, name)) {
        return h2_sos_h2_status_create(prev);
    }
    return prev;
}