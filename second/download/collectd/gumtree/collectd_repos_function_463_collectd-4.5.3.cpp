static int kread (u_long addr, void *buf, int size)
{
  int status;

  status = kvm_read (kvmd, addr, buf, size);
  if (status != size)
  {
    ERROR ("tcpconns plugin: kvm_read failed (got %i, expected %i): %s\n",
	status, size, kvm_geterr (kvmd));
    return (-1);
  }
  return (0);
}