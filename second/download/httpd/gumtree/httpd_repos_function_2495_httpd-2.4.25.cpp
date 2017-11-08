static void add_in(apr_bucket_brigade *bb, h2_session *s, int last) 
{
    bbout(bb, "    \"in\": {\n");
    bbout(bb, "      \"requests\": %d,\n", s->remote.emitted_count);
    bbout(bb, "      \"resets\": %d, \n", s->streams_reset);
    bbout(bb, "      \"frames\": %ld,\n", (long)s->frames_received);
    bbout(bb, "      \"octets\": %"APR_UINT64_T_FMT"\n", s->io.bytes_read);
    bbout(bb, "    }%s\n", last? "" : ",");
}