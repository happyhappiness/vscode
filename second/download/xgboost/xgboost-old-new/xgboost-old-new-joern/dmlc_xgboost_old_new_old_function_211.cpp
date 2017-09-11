virtual bool NextLine(std::string *out_data) {
    if (file_ptr_ >= file_ptr_end_ &&
        offset_curr_ >= offset_end_) return false;
    out_data->clear();
    while (true) {
      char c = reader_.GetChar();
      if (reader_.AtEnd()) {
        if (out_data->length() != 0) return true;
        file_ptr_ += 1;
        if (offset_curr_ != file_offset_[file_ptr_]) {
          utils::Error("warning:file size not calculated correctly\n");
          offset_curr_ = file_offset_[file_ptr_];
        }
        if (offset_curr_ >= offset_end_) return false;
        utils::Assert(file_ptr_ + 1 < file_offset_.size(),
                      "boundary check");
        delete fs_;
        fs_ = this->GetFile(file_ptr_);
        reader_.set_stream(fs_);
      } else {
        ++offset_curr_;
        if (c != '\r' && c != '\n' && c != EOF) {
          *out_data += c;
        } else {
          if (out_data->length() != 0) return true;
          if (file_ptr_ >= file_ptr_end_ &&
              offset_curr_ >= offset_end_) return false;
        }
      }
    }
  }