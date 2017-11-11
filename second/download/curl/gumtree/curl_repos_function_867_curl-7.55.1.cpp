static void
GetFileAndPassword(char *nextarg, char **file, char **password)
{
  char *certname, *passphrase;
  parse_cert_parameter(nextarg, &certname, &passphrase);
  Curl_safefree(*file);
  *file = certname;
  if(passphrase) {
    Curl_safefree(*password);
    *password = passphrase;
  }
  cleanarg(nextarg);
}