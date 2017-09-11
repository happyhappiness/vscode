      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
    }
    if (rabit::IsDistributed()) {
      this->SetParam("data_split", "col");
    }
    if (rabit::GetRank() != 0) {
      this->SetParam("silent", "2");
