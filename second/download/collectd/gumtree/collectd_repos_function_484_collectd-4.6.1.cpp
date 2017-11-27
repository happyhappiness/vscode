static int bind_xml_stats (int version, xmlDoc *doc, /* {{{ */
    xmlXPathContext *xpathCtx, xmlNode *statsnode)
{
  time_t current_time = 0;
  int status;

  xpathCtx->node = statsnode;

  /* TODO: Check `server/boot-time' to recognize server restarts. */

  status = bind_xml_read_timestamp ("server/current-time",
      doc, xpathCtx, &current_time);
  if (status != 0)
  {
    ERROR ("bind plugin: Reading `server/current-time' failed.");
    return (-1);
  }
  DEBUG ("bind plugin: Current server time is %i.", (int) current_time);

  /* XPath:     server/requests/opcode
   * Variables: QUERY, IQUERY, NOTIFY, UPDATE, ...
   * Layout:
   *   <opcode>
   *     <name>A</name>
   *     <counter>1</counter>
   *   </opcode>
   *   :
   */
  if (global_opcodes != 0)
  {
    list_info_ptr_t list_info =
    {
      /* plugin instance = */ "global-opcodes",
      /* type = */ "dns_opcode"
    };

    bind_parse_generic_name_value (/* xpath = */ "server/requests/opcode",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, xpathCtx, current_time);
  }

  /* XPath:     server/queries-in/rdtype
   * Variables: RESERVED0, A, NS, CNAME, SOA, MR, PTR, HINFO, MX, TXT, RP,
   *            X25, PX, AAAA, LOC, SRV, NAPTR, A6, DS, RRSIG, NSEC, DNSKEY,
   *            SPF, TKEY, IXFR, AXFR, ANY, ..., Others
   * Layout:
   *   <rdtype>
   *     <name>A</name>
   *     <counter>1</counter>
   *   </rdtype>
   *   :
   */
  if (global_qtypes != 0)
  {
    list_info_ptr_t list_info =
    {
      /* plugin instance = */ "global-qtypes",
      /* type = */ "dns_qtype"
    };

    bind_parse_generic_name_value (/* xpath = */ "server/queries-in/rdtype",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, xpathCtx, current_time);
  }
  
  /* XPath:     server/nsstats, server/nsstat
   * Variables: Requestv4, Requestv6, ReqEdns0, ReqBadEDNSVer, ReqTSIG,
   *            ReqSIG0, ReqBadSIG, ReqTCP, AuthQryRej, RecQryRej, XfrRej,
   *            UpdateRej, Response, TruncatedResp, RespEDNS0, RespTSIG,
   *            RespSIG0, QrySuccess, QryAuthAns, QryNoauthAns, QryReferral,
   *            QryNxrrset, QrySERVFAIL, QryFORMERR, QryNXDOMAIN, QryRecursion,
   *            QryDuplicate, QryDropped, QryFailure, XfrReqDone, UpdateReqFwd,
   *            UpdateRespFwd, UpdateFwdFail, UpdateDone, UpdateFail,
   *            UpdateBadPrereq
   * Layout v1:
   *   <nsstats>
   *     <Requestv4>1</Requestv4>
   *     <Requestv6>0</Requestv6>
   *     :
   *   </nsstats>
   * Layout v2:
   *   <nsstat>
   *     <name>Requestv4</name>
   *     <counter>1</counter>
   *   </nsstat>
   *   <nsstat>
   *     <name>Requestv6</name>
   *     <counter>0</counter>
   *   </nsstat>
   *   :
   */
  if (global_server_stats)
  {
    translation_table_ptr_t table_ptr =
    { 
      nsstats_translation_table,
      nsstats_translation_table_length,
      /* plugin_instance = */ "global-server_stats"
    };

    if (version == 1)
    {
      bind_parse_generic_value_list ("server/nsstats",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time, DS_TYPE_COUNTER);
    }
    else
    {
      bind_parse_generic_name_value ("server/nsstat",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time);
    }
  }

  /* XPath:     server/zonestats, server/zonestat
   * Variables: NotifyOutv4, NotifyOutv6, NotifyInv4, NotifyInv6, NotifyRej,
   *            SOAOutv4, SOAOutv6, AXFRReqv4, AXFRReqv6, IXFRReqv4, IXFRReqv6,
   *            XfrSuccess, XfrFail
   * Layout v1:
   *   <zonestats>
   *     <NotifyOutv4>0</NotifyOutv4>
   *     <NotifyOutv6>0</NotifyOutv6>
   *     :
   *   </zonestats>
   * Layout v2:
   *   <zonestat>
   *     <name>NotifyOutv4</name>
   *     <counter>0</counter>
   *   </zonestat>
   *   <zonestat>
   *     <name>NotifyOutv6</name>
   *     <counter>0</counter>
   *   </zonestat>
   *   :
   */
  if (global_zone_maint_stats)
  {
    translation_table_ptr_t table_ptr =
    { 
      zonestats_translation_table,
      zonestats_translation_table_length,
      /* plugin_instance = */ "global-zone_maint_stats"
    };

    if (version == 1)
    {
      bind_parse_generic_value_list ("server/zonestats",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time, DS_TYPE_COUNTER);
    }
    else
    {
      bind_parse_generic_name_value ("server/zonestat",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time);
    }
  }

  /* XPath:     server/resstats
   * Variables: Queryv4, Queryv6, Responsev4, Responsev6, NXDOMAIN, SERVFAIL,
   *            FORMERR, OtherError, EDNS0Fail, Mismatch, Truncated, Lame,
   *            Retry, GlueFetchv4, GlueFetchv6, GlueFetchv4Fail,
   *            GlueFetchv6Fail, ValAttempt, ValOk, ValNegOk, ValFail
   * Layout v1:
   *   <resstats>
   *     <Queryv4>0</Queryv4>
   *     <Queryv6>0</Queryv6>
   *     :
   *   </resstats>
   * Layout v2:
   *   <resstat>
   *     <name>Queryv4</name>
   *     <counter>0</counter>
   *   </resstat>
   *   <resstat>
   *     <name>Queryv6</name>
   *     <counter>0</counter>
   *   </resstat>
   *   :
   */
  if (global_resolver_stats != 0)
  {
    translation_table_ptr_t table_ptr =
    { 
      resstats_translation_table,
      resstats_translation_table_length,
      /* plugin_instance = */ "global-resolver_stats"
    };

    if (version == 1)
    {
      bind_parse_generic_value_list ("server/resstats",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time, DS_TYPE_COUNTER);
    }
    else
    {
      bind_parse_generic_name_value ("server/resstat",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time);
    }
  }

  /* XPath:  memory/summary
   * Variables: TotalUse, InUse, BlockSize, ContextSize, Lost
   * Layout: v2:
   *   <summary>
   *     <TotalUse>6587096</TotalUse>
   *     <InUse>1345424</InUse>
   *     <BlockSize>5505024</BlockSize>
   *     <ContextSize>3732456</ContextSize>
   *     <Lost>0</Lost>
   *   </summary>
   */
  if (global_memory_stats != 0)
  {
    translation_table_ptr_t table_ptr =
    {
      memsummary_translation_table,
      memsummary_translation_table_length,
      /* plugin_instance = */ "global-memory_stats"
    };

    bind_parse_generic_value_list ("memory/summary",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time, DS_TYPE_GAUGE);
  }

  if (views_num > 0)
    bind_xml_stats_search_views (version, doc, xpathCtx, statsnode,
        current_time);

  return 0;
}