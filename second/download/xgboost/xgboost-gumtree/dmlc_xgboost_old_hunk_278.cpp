      bst_uint fid = sorted_index_set[i];
      if (disk_offset_[fid] != curr_offset) {
        utils::Assert(disk_offset_[fid] > curr_offset, "fset index was not sorted");
        fi->Seek(begin + disk_offset_[fid]);
        curr_offset = disk_offset_[fid];
      }
      size_t j, size_to_read = 0;
