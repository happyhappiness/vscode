snprintf(imapc->resptag, sizeof(imapc->resptag), "%c%03d",
           'A' + curlx_sltosi(conn->connection_id % 26), imapc->cmdid);