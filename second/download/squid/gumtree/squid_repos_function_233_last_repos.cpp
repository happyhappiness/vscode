void
reply_done(int fd, void *data)
{
    struct _request *r = data;
    if (opt_range);     /* skip size checks for now */
    else if (strcmp(r->method, "HEAD") == 0);
    else if (r->bodysize != r->content_length && r->content_length >= 0)
        fprintf(stderr, "ERROR: %s got %d of %d bytes\n",
                r->url, r->bodysize, r->content_length);
    else if (r->validsize >= 0) {
        if (r->validsize != r->bodysize)
            fprintf(stderr, "WARNING: %s size mismatch wanted %d bytes got %d\n",
                    r->url, r->validsize, r->bodysize);
        else if (opt_checksum && r->validsum != r->sum)
            fprintf(stderr, "WARNING: %s invalid checksum wanted 0x%lx got 0x%lx\n",
                    r->url, r->validsum, r->sum);
    }
    if (r->validstatus && r->status != r->validstatus) {
        fprintf(stderr, "WARNING: %s status mismatch wanted %d got %d\n",
                r->url, r->validstatus, r->status);
    }
    if (trace_file) {
        if (opt_checksum)
            fprintf(trace_file, "%s %s %d %s %d 0x%lx\n",
                    r->method, r->url, r->status, r->requestbodyfile, r->bodysize, r->sum);
        else
            fprintf(trace_file, "%s %s %d %s %d\n",
                    r->method, r->url, r->status, r->requestbodyfile, r->bodysize);
    }
    free_request(r);
}