extern int preserve_times;
extern int always_checksum;
extern int checksum_seed;


extern int remote_version;
extern int verbose;

void setup_protocol(int f_out,int f_in)
{
  if (am_server) {
    remote_version = read_int(f_in);
    write_int(f_out,PROTOCOL_VERSION);
