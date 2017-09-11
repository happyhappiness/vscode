  }
  if (!strncmp(uri, "hdfs://", 7)) {
#if RABIT_USE_HDFS
    return new HDFSStream(hdfsConnect("default", 0), uri, mode);
#else
    utils::Error("Please compile with RABIT_USE_HDFS=1");
#endif
