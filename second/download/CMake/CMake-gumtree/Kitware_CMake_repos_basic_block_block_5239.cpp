f(mech->init) {
    ret = mech->init(conn->app_data);
    if(ret) {
      infof(data, "Failed initialization for %s. Skipping it.\n",
            mech->name);
      return CURLE_FAILED_INIT;
    }
  }