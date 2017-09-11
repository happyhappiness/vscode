      std::string pname = rabit::GetProcessorName();
      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
    }
    if (rabit::IsDistributed() && data_split == "NONE") {
      this->SetParam("dsplit", "row");
    }
    if (rabit::GetRank() != 0) {
