{
    int ret = 0;
    char *buf;
    void *enc;
    int len;
    if(!conn->sec_complete)
        return vfprintf(f, fmt, ap);
    
    buf = aprintf(fmt, ap);
    len = (conn->mech->encode)(conn->app_data, buf, strlen(buf),
                               conn->command_prot, &enc,
                               conn);
    free(buf);
    if(len < 0) {
        failf(conn->data, "Failed to encode command.");
        return -1;
    }
    if(Curl_base64_encode(enc, len, &buf) < 0){
      failf(conn->data, "Out of memory base64-encoding.");
      return -1;
    }
    if(conn->command_prot == prot_safe)
        ret = fprintf(f, "MIC %s", buf);
    else if(conn->command_prot == prot_private)
        ret = fprintf(f, "ENC %s", buf);
    else if(conn->command_prot == prot_confidential)
        ret = fprintf(f, "CONF %s", buf);

    free(buf);
    return ret;
}