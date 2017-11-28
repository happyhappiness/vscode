static void
icmpSquidRecv(int unused1, void *unused2)
{
    icmpEngine.Recv();
}