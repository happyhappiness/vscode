sprintf(buf, "%d%02d%02d %s %+05i", lctime->tm_year + 1900,
          lctime->tm_mon + 1, lctime->tm_mday,
          this->CTest->GetStopTime().c_str(), tzone_offset)