{

    uv_timer_stop(timer);
    uv_timer_again(timer);
    timer->timer_cb((uv_timer_t*) timer);
  }