static void add_streams(apr_bucket_brigade *bb, h2_session *s, int last) 
{
    stream_ctx_t x;
    
    x.bb = bb;
    x.s = s;
    x.idx = 0;
    bbout(bb, "  \"streams\": {");
    h2_mplx_stream_do(s->mplx, add_stream, &x);
    bbout(bb, "\n  }%s\n", last? "" : ",");
}