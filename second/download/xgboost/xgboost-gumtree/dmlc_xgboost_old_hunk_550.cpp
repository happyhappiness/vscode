    HandleCheckError(msg.c_str());
  }
}

/*! \brief replace fopen, report error when the file open fails */
inline FILE *FopenCheck(const char *fname, const char *flag) {
