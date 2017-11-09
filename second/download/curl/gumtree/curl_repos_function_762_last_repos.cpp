static HANDLE select_ws_wait(HANDLE handle, HANDLE event)
{
  struct select_ws_wait_data *data;
  HANDLE thread = NULL;

  /* allocate internal waiting data structure */
  data = malloc(sizeof(struct select_ws_wait_data));
  if(data) {
    data->handle = handle;
    data->event = event;

    /* launch waiting thread */
    thread = CreateThread(NULL, 0,
                          &select_ws_wait_thread,
                          data, 0, NULL);

    /* free data if thread failed to launch */
    if(!thread) {
      free(data);
    }
  }

  return thread;
}