static void service_statnode_process (pinba_statnode_t *node, /* {{{ */
    Pinba__Request* request)
{
  node->req_count++;

  float_counter_add (&node->req_time, request->request_time);
  float_counter_add (&node->ru_utime, request->ru_utime);
  float_counter_add (&node->ru_stime, request->ru_stime);

  node->doc_size += request->document_size;

  if (isnan (node->mem_peak)
      || (node->mem_peak < ((gauge_t) request->memory_peak)))
    node->mem_peak = (gauge_t) request->memory_peak;

}