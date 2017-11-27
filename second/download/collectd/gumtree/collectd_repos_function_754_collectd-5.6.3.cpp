const char *qtype_str(int t) {
  static char buf[32];
  switch (t) {
#if (defined(__NAMESER)) && (__NAMESER >= 19991001)
  case ns_t_a:
    return ("A");
  case ns_t_ns:
    return ("NS");
  case ns_t_md:
    return ("MD");
  case ns_t_mf:
    return ("MF");
  case ns_t_cname:
    return ("CNAME");
  case ns_t_soa:
    return ("SOA");
  case ns_t_mb:
    return ("MB");
  case ns_t_mg:
    return ("MG");
  case ns_t_mr:
    return ("MR");
  case ns_t_null:
    return ("NULL");
  case ns_t_wks:
    return ("WKS");
  case ns_t_ptr:
    return ("PTR");
  case ns_t_hinfo:
    return ("HINFO");
  case ns_t_minfo:
    return ("MINFO");
  case ns_t_mx:
    return ("MX");
  case ns_t_txt:
    return ("TXT");
  case ns_t_rp:
    return ("RP");
  case ns_t_afsdb:
    return ("AFSDB");
  case ns_t_x25:
    return ("X25");
  case ns_t_isdn:
    return ("ISDN");
  case ns_t_rt:
    return ("RT");
  case ns_t_nsap:
    return ("NSAP");
  case ns_t_nsap_ptr:
    return ("NSAP-PTR");
  case ns_t_sig:
    return ("SIG");
  case ns_t_key:
    return ("KEY");
  case ns_t_px:
    return ("PX");
  case ns_t_gpos:
    return ("GPOS");
  case ns_t_aaaa:
    return ("AAAA");
  case ns_t_loc:
    return ("LOC");
  case ns_t_nxt:
    return ("NXT");
  case ns_t_eid:
    return ("EID");
  case ns_t_nimloc:
    return ("NIMLOC");
  case ns_t_srv:
    return ("SRV");
  case ns_t_atma:
    return ("ATMA");
  case ns_t_naptr:
    return ("NAPTR");
  case ns_t_opt:
    return ("OPT");
#if __NAMESER >= 19991006
  case ns_t_kx:
    return ("KX");
  case ns_t_cert:
    return ("CERT");
  case ns_t_a6:
    return ("A6");
  case ns_t_dname:
    return ("DNAME");
  case ns_t_sink:
    return ("SINK");
  case ns_t_tsig:
    return ("TSIG");
#endif
#if __NAMESER >= 20090302
  case ns_t_apl:
    return ("APL");
  case ns_t_ds:
    return ("DS");
  case ns_t_sshfp:
    return ("SSHFP");
  case ns_t_ipseckey:
    return ("IPSECKEY");
  case ns_t_rrsig:
    return ("RRSIG");
  case ns_t_nsec:
    return ("NSEC");
  case ns_t_dnskey:
    return ("DNSKEY");
  case ns_t_dhcid:
    return ("DHCID");
  case ns_t_nsec3:
    return ("NSEC3");
  case ns_t_nsec3param:
    return ("NSEC3PARAM");
  case ns_t_hip:
    return ("HIP");
  case ns_t_spf:
    return ("SPF");
  case ns_t_ixfr:
    return ("IXFR");
#endif
  case ns_t_axfr:
    return ("AXFR");
  case ns_t_mailb:
    return ("MAILB");
  case ns_t_maila:
    return ("MAILA");
  case ns_t_any:
    return ("ANY");
#if __NAMESER >= 19991006
  case ns_t_zxfr:
    return ("ZXFR");
#endif
#if __NAMESER >= 20090302
  case ns_t_dlv:
    return ("DLV");
#endif
/* #endif __NAMESER >= 19991001 */
#elif (defined(__BIND)) && (__BIND >= 19950621)
  case T_A:
    return ("A"); /* 1 ... */
  case T_NS:
    return ("NS");
  case T_MD:
    return ("MD");
  case T_MF:
    return ("MF");
  case T_CNAME:
    return ("CNAME");
  case T_SOA:
    return ("SOA");
  case T_MB:
    return ("MB");
  case T_MG:
    return ("MG");
  case T_MR:
    return ("MR");
  case T_NULL:
    return ("NULL");
  case T_WKS:
    return ("WKS");
  case T_PTR:
    return ("PTR");
  case T_HINFO:
    return ("HINFO");
  case T_MINFO:
    return ("MINFO");
  case T_MX:
    return ("MX");
  case T_TXT:
    return ("TXT");
  case T_RP:
    return ("RP");
  case T_AFSDB:
    return ("AFSDB");
  case T_X25:
    return ("X25");
  case T_ISDN:
    return ("ISDN");
  case T_RT:
    return ("RT");
  case T_NSAP:
    return ("NSAP");
  case T_NSAP_PTR:
    return ("NSAP_PTR");
  case T_SIG:
    return ("SIG");
  case T_KEY:
    return ("KEY");
  case T_PX:
    return ("PX");
  case T_GPOS:
    return ("GPOS");
  case T_AAAA:
    return ("AAAA");
  case T_LOC:
    return ("LOC");
  case T_NXT:
    return ("NXT");
  case T_EID:
    return ("EID");
  case T_NIMLOC:
    return ("NIMLOC");
  case T_SRV:
    return ("SRV");
  case T_ATMA:
    return ("ATMA");
  case T_NAPTR:
    return ("NAPTR"); /* ... 35 */
#if (__BIND >= 19960801)
  case T_KX:
    return ("KX"); /* 36 ... */
  case T_CERT:
    return ("CERT");
  case T_A6:
    return ("A6");
  case T_DNAME:
    return ("DNAME");
  case T_SINK:
    return ("SINK");
  case T_OPT:
    return ("OPT");
  case T_APL:
    return ("APL");
  case T_DS:
    return ("DS");
  case T_SSHFP:
    return ("SSHFP");
  case T_RRSIG:
    return ("RRSIG");
  case T_NSEC:
    return ("NSEC");
  case T_DNSKEY:
    return ("DNSKEY"); /* ... 48 */
  case T_TKEY:
    return ("TKEY"); /* 249 */
#endif /* __BIND >= 19960801 */
  case T_TSIG:
    return ("TSIG"); /* 250 ... */
  case T_IXFR:
    return ("IXFR");
  case T_AXFR:
    return ("AXFR");
  case T_MAILB:
    return ("MAILB");
  case T_MAILA:
    return ("MAILA");
  case T_ANY:
    return ("ANY"); /* ... 255 */
#endif /* __BIND >= 19950621 */
  default:
    ssnprintf(buf, sizeof(buf), "#%i", t);
    return (buf);
  } /* switch (t) */
}