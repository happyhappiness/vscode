static int cxmms_read(void) {
  gint rate;
  gint freq;
  gint nch;

  if (!xmms_remote_is_running(xmms_session))
    return (0);

  xmms_remote_get_info(xmms_session, &rate, &freq, &nch);

  if ((freq == 0) || (nch == 0))
    return (-1);

  cxmms_submit("bitrate", rate);
  cxmms_submit("frequency", freq);

  return (0);
}