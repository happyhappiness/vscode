{
    /* We lost the race. Destroy the event we created and wait for the */
    /* existing one to become signaled. */
    CloseHandle(created_event);
    result = WaitForSingleObject(existing_event, INFINITE);
    assert(result == WAIT_OBJECT_0);
  }