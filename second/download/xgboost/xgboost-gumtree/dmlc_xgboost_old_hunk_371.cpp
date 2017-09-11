      std::string pname = rabit::GetProcessorName();
      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
    }
    if (rabit::IsDistributed()) {
      this->SetParam("dsplit", "row");
    }
    if (rabit::GetRank() != 0) {
