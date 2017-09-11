      if (reader_.AtEnd()) {
        if (out_data->length() != 0) return true;
        file_ptr_ += 1;
        if (offset_curr_ >= offset_end_) return false;
        if (offset_curr_ != file_offset_[file_ptr_]) {
          utils::Error("warning: FILE size not calculated correctly\n");
          offset_curr_ = file_offset_[file_ptr_];
        }
        utils::Assert(file_ptr_ + 1 < file_offset_.size(),
                      "boundary check");
        delete fs_;
        fs_ = provider_->Open(file_ptr_);
        reader_.set_stream(fs_);
      } else {
        ++offset_curr_;
