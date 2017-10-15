    control->core()->push_log_std("Could not open XMLRPC log file '" + m_xmlrpcLog + "'.");
    return;
  }

  control->core()->push_log_std("Logging XMLRPC events to '" + m_xmlrpcLog + "'.");
}
