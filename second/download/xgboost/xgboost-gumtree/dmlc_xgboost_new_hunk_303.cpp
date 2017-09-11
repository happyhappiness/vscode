  }
  if (!strncmp(uri, "hdfs://", 7)) {
#if RABIT_USE_HDFS
    return new HDFSStream(hdfsConnect(HDFSStream::GetNameNode().c_str(), 0),
                          uri, mode, true);
#else
    utils::Error("Please compile with RABIT_USE_HDFS=1");
#endif
