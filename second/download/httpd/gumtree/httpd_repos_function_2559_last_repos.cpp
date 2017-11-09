static void add_settings(apr_bucket_brigade *bb, h2_session *s, int last) 
{
    h2_mplx *m = s->mplx;
    
    bbout(bb, "  \"settings\": {\n");
    bbout(bb, "    \"SETTINGS_MAX_CONCURRENT_STREAMS\": %d,\n", m->max_streams); 
    bbout(bb, "    \"SETTINGS_MAX_FRAME_SIZE\": %d,\n", 16*1024); 
    bbout(bb, "    \"SETTINGS_INITIAL_WINDOW_SIZE\": %d,\n",
          h2_config_geti(s->config, H2_CONF_WIN_SIZE));
    bbout(bb, "    \"SETTINGS_ENABLE_PUSH\": %d\n", h2_session_push_enabled(s)); 
    bbout(bb, "  }%s\n", last? "" : ",");
}