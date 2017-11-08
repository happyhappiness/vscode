static int is_mpm_running(void)
{
    int mpm_state = 0;

    if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
      return 0;
    }
  
    if (mpm_state == AP_MPMQ_STOPPING) {
      return 0;
    }

    return 1;
}