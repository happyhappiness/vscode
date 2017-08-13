                 << static_cast<int>(percent + .5f) << "% tests passed, "
                 << failed.size() << " tests failed out of " << total
                 << std::endl);

    if (!this->CTest->GetLabelsForSubprojects().empty() &&
        this->CTest->GetSubprojectSummary()) {
      this->PrintSubprojectSummary();
    } else if (this->CTest->GetLabelSummary()) {
      this->PrintLabelSummary();
    }

    char realBuf[1024];
    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
