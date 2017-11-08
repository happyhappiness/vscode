void tftp_set_timeouts(tftp_state_data_t *state)
{

  struct SessionHandle *data = state->conn->data;
  time_t maxtime, timeout;

  time(&state->start_time);
  if(state->state == TFTP_STATE_START) {
    /* Compute drop-dead time */
    maxtime = (time_t)(data->set.connecttimeout?data->set.connecttimeout:30);
    state->max_time = state->start_time+maxtime;

    /* Set per-block timeout to total */
    timeout = maxtime ;

    /* Average restart after 5 seconds */
    state->retry_max = timeout/5;

    /* Compute the re-start interval to suit the timeout */
    state->retry_time = timeout/state->retry_max;
    if(state->retry_time<1) state->retry_time=1;

  }
  else {

    /* Compute drop-dead time */
    maxtime = data->set.timeout?data->set.timeout:3600;
    state->max_time = state->start_time+maxtime;

    /* Set per-block timeout to 10% of total */
    timeout = maxtime/10 ;

    /* Average reposting an ACK after 15 seconds */
    state->retry_max = timeout/15;
  }
  /* But bound the total number  */
  if(state->retry_max<3) state->retry_max=3;
  if(state->retry_max>50) state->retry_max=50;

  /* Compute the re-ACK interval to suit the timeout */
  state->retry_time = timeout/state->retry_max;
  if(state->retry_time<1) state->retry_time=1;

  infof(data, "set timeouts for state %d; Total %d, retry %d maxtry %d\n",
        state->state, (state->max_time-state->start_time),
        state->retry_time, state->retry_max);
}