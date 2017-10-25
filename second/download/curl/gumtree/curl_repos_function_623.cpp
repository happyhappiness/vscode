static int
krb4_encode(void *app_data, void *from, int length, int level, void **to,
            struct connectdata *conn)
{
  struct krb4_data *d = app_data;
  *to = malloc(length + 31);
  if(level == prot_safe)
    return krb_mk_safe(from, *to, length, &d->key,
                       (struct sockaddr_in *)LOCAL_ADDR,
                       (struct sockaddr_in *)REMOTE_ADDR);
  else if(level == prot_private)
    return krb_mk_priv(from, *to, length, d->schedule, &d->key,
                       (struct sockaddr_in *)LOCAL_ADDR,
                       (struct sockaddr_in *)REMOTE_ADDR);
  else
    return -1;
}