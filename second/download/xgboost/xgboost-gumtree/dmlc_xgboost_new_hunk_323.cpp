        if (out_data->length() != 0) return true;
        file_ptr_ += 1;
        if (offset_curr_ != file_offset_[file_ptr_]) {
          utils::Error("warning:std::FILE size not calculated correctly\n");
          offset_curr_ = file_offset_[file_ptr_];
        }
        if (offset_curr_ >= offset_end_) return false;
