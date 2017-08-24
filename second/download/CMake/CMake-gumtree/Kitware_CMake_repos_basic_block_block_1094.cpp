{
  if (!cp) {
    return;
  }
  cp->Timeout = timeout;
  if (cp->Timeout < 0) {
    cp->Timeout = 0;
  }
  // Force recomputation of TimeoutTime.
  cp->TimeoutTime.tv_sec = -1;
}