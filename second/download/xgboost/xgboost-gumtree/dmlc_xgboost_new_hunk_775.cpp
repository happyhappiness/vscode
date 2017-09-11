                    utils::Assert(fi.Read(&data[0], data.size() * sizeof(REntry)), "Load FMatrixS");
                }
            }
        public:
            /*! \brief row pointer of CSR sparse storage */
            std::vector<size_t>  row_ptr_;
            /*! \brief data in the row */
