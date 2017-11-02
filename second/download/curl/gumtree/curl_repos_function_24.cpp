void start_timeout(CURLM *multi, long timeout_ms, void *userp)
{
  if(timeout_ms <= 0)
    timeout_ms = 1; /* 0 means directly call socket_action, but we'll do it in
                       a bit */
  uv_timer_start(&timeout, on_timeout, timeout_ms, 0);
}