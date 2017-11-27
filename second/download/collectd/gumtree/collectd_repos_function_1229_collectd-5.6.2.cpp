static int chrony_query(const int p_command, tChrony_Request *p_req,
                        tChrony_Response *p_resp, size_t *p_resp_size) {
  /* Check connection. We simply perform one try as collectd already handles
   * retries */
  assert(p_req);
  assert(p_resp);
  assert(p_resp_size);

  if (g_chrony_is_connected == 0) {
    if (chrony_connect() == CHRONY_RC_OK) {
      g_chrony_is_connected = 1;
    } else {
      ERROR(PLUGIN_NAME ": Unable to connect. Errno = %d", errno);
      return CHRONY_RC_FAIL;
    }
  }

  do {
    int valid_command = 0;
    size_t req_size = sizeof(p_req->header) + sizeof(p_req->padding);
    size_t resp_size = sizeof(p_resp->header);
    uint16_t resp_code = RPY_NULL;
    switch (p_command) {
    case REQ_TRACKING:
      req_size += sizeof(p_req->body.tracking);
      resp_size += sizeof(p_resp->body.tracking);
      resp_code = RPY_TRACKING;
      valid_command = 1;
      break;
    case REQ_N_SOURCES:
      req_size += sizeof(p_req->body.n_sources);
      resp_size += sizeof(p_resp->body.n_sources);
      resp_code = RPY_N_SOURCES;
      valid_command = 1;
      break;
    case REQ_SOURCE_DATA:
      req_size += sizeof(p_req->body.source_data);
      resp_size += sizeof(p_resp->body.source_data);
      resp_code = RPY_SOURCE_DATA;
      valid_command = 1;
      break;
    case REQ_SOURCE_STATS:
      req_size += sizeof(p_req->body.source_stats);
      resp_size += sizeof(p_resp->body.source_stats);
      resp_code = RPY_SOURCE_STATS;
      valid_command = 1;
      break;
    default:
      ERROR(PLUGIN_NAME ": Unknown request command (Was: %d)", p_command);
      break;
    }

    if (valid_command == 0)
      break;

    uint32_t seq_nr = rand_r(&g_chrony_rand);
    p_req->header.f_cmd = htons(p_command);
    p_req->header.f_cmd_try = 0;
    p_req->header.f_seq = seq_nr;

    DEBUG(PLUGIN_NAME ": Sending request (.cmd = %d, .seq = %d)", p_command,
          seq_nr);
    if (chrony_send_request(p_req, req_size) != 0)
      break;

    DEBUG(PLUGIN_NAME ": Waiting for response");
    if (chrony_recv_response(p_resp, resp_size, p_resp_size) != 0)
      break;

    DEBUG(PLUGIN_NAME ": Received response: .version = %u, .type = %u, .cmd = "
                      "%u, .reply = %u, .status = %u, .seq = %u",
          p_resp->header.f_version, p_resp->header.f_type,
          ntohs(p_resp->header.f_cmd), ntohs(p_resp->header.f_reply),
          ntohs(p_resp->header.f_status), p_resp->header.f_seq);

    if (p_resp->header.f_version != p_req->header.f_version) {
      ERROR(PLUGIN_NAME ": Wrong protocol version (Was: %d, expected: %d)",
            p_resp->header.f_version, p_req->header.f_version);
      return CHRONY_RC_FAIL;
    }
    if (p_resp->header.f_type != PKT_TYPE_CMD_REPLY) {
      ERROR(PLUGIN_NAME ": Wrong packet type (Was: %d, expected: %d)",
            p_resp->header.f_type, PKT_TYPE_CMD_REPLY);
      return CHRONY_RC_FAIL;
    }
    if (p_resp->header.f_seq != seq_nr) {
      /* FIXME: Implement sequence number handling */
      ERROR(PLUGIN_NAME ": Unexpected sequence number (Was: %d, expected: %d)",
            p_resp->header.f_seq, p_req->header.f_seq);
      return CHRONY_RC_FAIL;
    }
    if (p_resp->header.f_cmd != p_req->header.f_cmd) {
      ERROR(PLUGIN_NAME ": Wrong reply command (Was: %d, expected: %d)",
            p_resp->header.f_cmd, p_req->header.f_cmd);
      return CHRONY_RC_FAIL;
    }

    if (ntohs(p_resp->header.f_reply) != resp_code) {
      ERROR(PLUGIN_NAME ": Wrong reply code (Was: %d, expected: %d)",
            ntohs(p_resp->header.f_reply), resp_code);
      return CHRONY_RC_FAIL;
    }

    switch (p_resp->header.f_status) {
    case STT_SUCCESS:
      DEBUG(PLUGIN_NAME ": Reply packet status STT_SUCCESS");
      break;
    default:
      ERROR(PLUGIN_NAME
            ": Reply packet contains error status: %d (expected: %d)",
            p_resp->header.f_status, STT_SUCCESS);
      return CHRONY_RC_FAIL;
    }

    /* Good result */
    return CHRONY_RC_OK;
  } while (0);

  /* Some error occured */
  return CHRONY_RC_FAIL;
}