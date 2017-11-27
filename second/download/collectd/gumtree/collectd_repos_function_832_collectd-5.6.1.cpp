static void bind_xml_stats_v3 (xmlDoc *doc, /* {{{ */
    xmlXPathContext *xpathCtx, xmlNode *statsnode, time_t current_time)
{
  /* XPath:     server/counters[@type='opcode']
   * Variables: QUERY, IQUERY, NOTIFY, UPDATE, ...
   * Layout v3:
   *   <counters type="opcode">
   *     <counter name="A">1</counter>
   *     :
   *   </counters>
   */
  if (global_opcodes != 0)
  {
    list_info_ptr_t list_info =
    {
      /* plugin instance = */ "global-opcodes",
      /* type = */ "dns_opcode"
    };
    bind_parse_generic_name_attr_value_list (/* xpath = */ "server/counters[@type='opcode']",
      /* callback = */ bind_xml_list_callback,
      /* user_data = */ &list_info,
      doc, xpathCtx, current_time, DS_TYPE_COUNTER);
  }

  /* XPath:     server/counters[@type='qtype']
   * Variables: RESERVED0, A, NS, CNAME, SOA, MR, PTR, HINFO, MX, TXT, RP,
   *            X25, PX, AAAA, LOC, SRV, NAPTR, A6, DS, RRSIG, NSEC, DNSKEY,
   *            SPF, TKEY, IXFR, AXFR, ANY, ..., Others
   * Layout v3:
   *   <counters type="opcode">
   *     <counter name="A">1</counter>
   *     :
   *   </counters>
   */
  if (global_qtypes != 0)
  {
    list_info_ptr_t list_info =
    {
      /* plugin instance = */ "global-qtypes",
      /* type = */ "dns_qtype"
    };

    bind_parse_generic_name_attr_value_list (/* xpath = */ "server/counters[@type='qtype']",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, xpathCtx, current_time, DS_TYPE_COUNTER);
  }

  /* XPath:     server/counters[@type='nsstat']
   * Variables: Requestv4, Requestv6, ReqEdns0, ReqBadEDNSVer, ReqTSIG,
   *            ReqSIG0, ReqBadSIG, ReqTCP, AuthQryRej, RecQryRej, XfrRej,
   *            UpdateRej, Response, TruncatedResp, RespEDNS0, RespTSIG,
   *            RespSIG0, QrySuccess, QryAuthAns, QryNoauthAns, QryReferral,
   *            QryNxrrset, QrySERVFAIL, QryFORMERR, QryNXDOMAIN, QryRecursion,
   *            QryDuplicate, QryDropped, QryFailure, XfrReqDone, UpdateReqFwd,
   *            UpdateRespFwd, UpdateFwdFail, UpdateDone, UpdateFail,
   *            UpdateBadPrereq
   * Layout v3:
   *   <counters type="nsstat"
   *     <counter name="Requestv4">1</counter>
   *     <counter name="Requestv6">0</counter>
   *     :
   *   </counter>
   */
  if (global_server_stats)
  {
    translation_table_ptr_t table_ptr =
    {
      nsstats_translation_table,
      nsstats_translation_table_length,
      /* plugin_instance = */ "global-server_stats"
    };

    bind_parse_generic_name_attr_value_list ("server/counters[@type='nsstat']",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, xpathCtx, current_time, DS_TYPE_COUNTER);
  }

  /* XPath:     server/zonestats, server/zonestat, server/counters[@type='zonestat']
   * Variables: NotifyOutv4, NotifyOutv6, NotifyInv4, NotifyInv6, NotifyRej,
   *            SOAOutv4, SOAOutv6, AXFRReqv4, AXFRReqv6, IXFRReqv4, IXFRReqv6,
   *            XfrSuccess, XfrFail
   * Layout v3:
   *   <counters type="zonestat"
   *     <counter name="NotifyOutv4">0</counter>
   *     <counter name="NotifyOutv6">0</counter>
   *     :
   *   </counter>
   */
  if (global_zone_maint_stats)
  {
    translation_table_ptr_t table_ptr =
    {
      zonestats_translation_table,
      zonestats_translation_table_length,
      /* plugin_instance = */ "global-zone_maint_stats"
    };

    bind_parse_generic_name_attr_value_list ("server/counters[@type='zonestat']",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, xpathCtx, current_time, DS_TYPE_COUNTER);
  }

  /* XPath:     server/resstats, server/counters[@type='resstat']
   * Variables: Queryv4, Queryv6, Responsev4, Responsev6, NXDOMAIN, SERVFAIL,
   *            FORMERR, OtherError, EDNS0Fail, Mismatch, Truncated, Lame,
   *            Retry, GlueFetchv4, GlueFetchv6, GlueFetchv4Fail,
   *            GlueFetchv6Fail, ValAttempt, ValOk, ValNegOk, ValFail
   * Layout v3:
   *   <counters type="resstat"
   *     <counter name="Queryv4">0</counter>
   *     <counter name="Queryv6">0</counter>
   *     :
   *   </counter>
   */
  if (global_resolver_stats != 0)
  {
    translation_table_ptr_t table_ptr =
    {
      resstats_translation_table,
      resstats_translation_table_length,
      /* plugin_instance = */ "global-resolver_stats"
    };

    bind_parse_generic_name_attr_value_list ("server/counters[@type='resstat']",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, xpathCtx, current_time, DS_TYPE_COUNTER);
  }
}