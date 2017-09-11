  virtual void InitAfterException(void) {
    utils::Error("InitAfterException: not implemented");
  }
  /*!
   * \brief report current status to the job tracker
   * depending on the job tracker we are in
   */
  inline void ReportStatus(void) const {
