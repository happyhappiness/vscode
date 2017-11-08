static void dump_addrinfo(struct connectdata *conn, const Curl_addrinfo *ai)
{
  printf("dump_addrinfo:\n");
  for(; ai; ai = ai->ai_next) {
    char  buf[INET6_ADDRSTRLEN];

    printf("    fam %2d, CNAME %s, ",
           ai->ai_family, ai->ai_canonname ? ai->ai_canonname : "<none>");
    if(Curl_printable_address(ai, buf, sizeof(buf)))
      printf("%s\n", buf);
    else
      printf("failed; %s\n", Curl_strerror(conn, SOCKERRNO));
  }
}