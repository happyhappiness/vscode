static void mysignal(int sig, void (*handler)(int))
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handler;
  sigaction(sig, &sa, NULL);
}