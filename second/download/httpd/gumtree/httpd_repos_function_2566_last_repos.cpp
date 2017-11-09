static void add_stats(apr_bucket_brigade *bb, h2_session *s, 
                     h2_stream *stream, int last) 
{
    bbout(bb, "  \"stats\": {\n");
    add_in(bb, s, 0);
    add_out(bb, s, 0);
    add_push(bb, s, stream, 1);
    bbout(bb, "  }%s\n", last? "" : ",");
}