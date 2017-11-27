static void *ovs_event_worker(void *arg) {
  ovs_db_t *pdb = (ovs_db_t *)arg;

  while (pdb->event_thread.value != OVS_DB_EVENT_TERMINATE) {
    /* wait for an event */
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += (OVS_DB_EVENT_TIMEOUT);
    int ret = pthread_cond_timedwait(&pdb->event_thread.cond,
                                     &pdb->event_thread.mutex, &ts);
    if (!ret) {
      /* handle the event */
      OVS_DEBUG("handle event %d", pdb->event_thread.value);
      switch (pdb->event_thread.value) {
      case OVS_DB_EVENT_CONN_ESTABLISHED:
        if (pdb->cb.post_conn_init)
          pdb->cb.post_conn_init(pdb);
        break;
      case OVS_DB_EVENT_CONN_TERMINATED:
        if (pdb->cb.post_conn_terminate)
          pdb->cb.post_conn_terminate();
        break;
      default:
        OVS_DEBUG("unknown event received");
        break;
      }
    } else if (ret == ETIMEDOUT) {
      /* wait timeout */
      OVS_DEBUG("no event received (timeout)");
      continue;
    } else {
      /* unexpected error */
      OVS_ERROR("pthread_cond_timedwait() failed");
      break;
    }
  }

  OVS_DEBUG("event thread has been completed");
  return NULL;
}