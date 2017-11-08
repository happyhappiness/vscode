static void add_out(apr_bucket_brigade *bb, h2_session *s, int last) 
{
    bbout(bb, "    \"out\": {\n");
    bbout(bb, "      \"responses\": %d,\n", s->responses_submitted);
    bbout(bb, "      \"frames\": %ld,\n", (long)s->frames_sent);
    bbout(bb, "      \"octets\": %"APR_UINT64_T_FMT"\n", s->io.bytes_written);
    bbout(bb, "    }%s\n", last? "" : ",");
}