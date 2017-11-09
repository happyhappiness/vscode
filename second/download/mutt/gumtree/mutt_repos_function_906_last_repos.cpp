static int check_certificate_by_digest (X509 *peercert)
{
  return check_certificate_expiration (peercert, 0) &&
    check_certificate_file (peercert);
}