int
Curl_sec_read_msg(struct connectdata *conn, char *s, int level)
{
    int len;
    char *buf;
    int code;
    
    buf = malloc(strlen(s));
    len = Curl_base64_decode(s + 4, buf); /* XXX */
    
    len = (conn->mech->decode)(conn->app_data, buf, len, level, conn);
    if(len < 0)
	return -1;
    
    buf[len] = '\0';

    if(buf[3] == '-')
	code = 0;
    else
	sscanf(buf, "%d", &code);
    if(buf[len-1] == '\n')
	buf[len-1] = '\0';
    strcpy(s, buf);
    free(buf);
    return code;
}