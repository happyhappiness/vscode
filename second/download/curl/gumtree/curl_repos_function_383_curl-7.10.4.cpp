static int
krb4_decode(void *app_data, void *buf, int len, int level,
	    struct connectdata *conn)
{
    MSG_DAT m;
    int e;
    struct krb4_data *d = app_data;
    
    if(level == prot_safe)
	e = krb_rd_safe(buf, len, &d->key,
			(struct sockaddr_in *)REMOTE_ADDR,
			(struct sockaddr_in *)LOCAL_ADDR, &m);
    else
	e = krb_rd_priv(buf, len, d->schedule, &d->key, 
			(struct sockaddr_in *)REMOTE_ADDR,
			(struct sockaddr_in *)LOCAL_ADDR, &m);
    if(e){
	syslog(LOG_ERR, "krb4_decode: %s", krb_get_err_text(e));
	return -1;
    }
    memmove(buf, m.app_data, m.app_length);
    return m.app_length;
}