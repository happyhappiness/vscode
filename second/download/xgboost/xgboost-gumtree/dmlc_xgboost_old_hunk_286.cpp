   * \param uri the uri of the input, can contain hdfs prefix
   * \param part_index the part id of current input
   * \param num_parts total number of splits
   * \return a created input split
   */
  static InputSplit* Create(const char *uri,
                            unsigned part_index,
                            unsigned num_parts);
};

// implementations of inline functions
template<typename T>
inline void Stream::Write(const std::vector<T> &vec) {
