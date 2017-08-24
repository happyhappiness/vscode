{
    req = &handle->poll_req_1;
    handle->submitted_events_1 = handle->events;
    handle->mask_events_1 = 0;
    handle->mask_events_2 = handle->events;
  }