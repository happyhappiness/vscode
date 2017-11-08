static void dump_addrinfo (struct connectdata *conn, const struct addrinfo *ai)
{
  TRACE(("dump_addrinfo:\n"));
  for ( ; ai; ai = ai->ai_next) {
    char  buf [INET6_ADDRSTRLEN];

    trace_it("    fam %2d, CNAME %s, ",
             ai->ai_family, ai->ai_canonname ? ai->ai_canonname : "<none>");
    if (Curl_printable_address(ai, buf, sizeof(buf)))
      trace_it("%s\n", buf);
    else
      trace_it("failed; %s\n", Curl_strerror(conn,WSAGetLastError()));
  }
}