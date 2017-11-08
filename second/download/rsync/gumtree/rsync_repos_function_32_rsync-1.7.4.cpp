void setup_nonblocking(int f_in,int f_out)
{
  set_blocking(f_out,0);
  buffer_f_in = f_in;
}