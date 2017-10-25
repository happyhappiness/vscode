enum protection_level
Curl_set_command_prot(struct connectdata *conn, enum protection_level level)
{
  enum protection_level old = conn->command_prot;
  conn->command_prot = level;
  return old;
}