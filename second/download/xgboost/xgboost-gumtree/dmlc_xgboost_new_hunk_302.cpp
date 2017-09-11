    return new SingleFileSplit(uri);
  }
  if (!strncmp(uri, "file://", 7)) {
    return new LineSplitter(new FileProvider(uri), part, nsplit);
  }
  if (!strncmp(uri, "hdfs://", 7)) {
#if RABIT_USE_HDFS
    return new LineSplitter(new HDFSProvider(uri), part, nsplit);
#else
    utils::Error("Please compile with RABIT_USE_HDFS=1");
#endif
  }
  return new LineSplitter(new FileProvider(uri), part, nsplit);
}
/*!
 * \brief create an stream, the stream must be able to close
