static int conn_read (void)
{
  int errors_num = 0;

  conn_reset_port_entry ();

  if (conn_read_file ("/proc/net/tcp") != 0)
    errors_num++;
  if (conn_read_file ("/proc/net/tcp6") != 0)
    errors_num++;

  if (errors_num < 2)
  {
    conn_submit_all ();
  }
  else
  {
    ERROR ("tcpconns plugin: Neither /proc/net/tcp nor /proc/net/tcp6 "
	"coult be read.");
    return (-1);
  }

  return (0);
}