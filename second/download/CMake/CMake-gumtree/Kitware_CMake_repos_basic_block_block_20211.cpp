(file_info.BasicInformation.FileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      statbuf->st_mode |= _S_IFDIR;
      statbuf->st_size = 0;
    } else {
      statbuf->st_mode |= _S_IFREG;
      statbuf->st_size = file_info.StandardInformation.EndOfFile.QuadPart;
    }