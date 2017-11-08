void h2_iq_append(h2_iqueue *q, int sid)
{
    h2_iq_add(q, sid, NULL, NULL);
}