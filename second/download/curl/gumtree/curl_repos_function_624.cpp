static int
mk_auth(struct krb4_data *d, KTEXT adat,
        const char *service, char *host, int checksum)
{
  int ret;
  CREDENTIALS cred;
  char sname[SNAME_SZ], inst[INST_SZ], realm[REALM_SZ];

  strlcpy(sname, service, sizeof(sname));
  strlcpy(inst, krb_get_phost(host), sizeof(inst));
  strlcpy(realm, krb_realmofhost(host), sizeof(realm));
  ret = krb_mk_req(adat, sname, inst, realm, checksum);
  if(ret)
    return ret;
  strlcpy(sname, service, sizeof(sname));
  strlcpy(inst, krb_get_phost(host), sizeof(inst));
  strlcpy(realm, krb_realmofhost(host), sizeof(realm));
  ret = krb_get_cred(sname, inst, realm, &cred);
  memmove(&d->key, &cred.session, sizeof(des_cblock));
  des_key_sched(&d->key, d->schedule);
  memset(&cred, 0, sizeof(cred));
  return ret;
}