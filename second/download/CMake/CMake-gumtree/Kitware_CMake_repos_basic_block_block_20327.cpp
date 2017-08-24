{
          name_len = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         addrinfow_ptr->ai_canonname,
                                         -1,
                                         NULL,
                                         0,
                                         NULL,
                                         NULL);
          assert(name_len > 0);
          assert(cur_ptr + name_len <= alloc_ptr + addrinfo_len);
          name_len = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         addrinfow_ptr->ai_canonname,
                                         -1,
                                         cur_ptr,
                                         name_len,
                                         NULL,
                                         NULL);
          assert(name_len > 0);
          addrinfo_ptr->ai_canonname = cur_ptr;
          cur_ptr += ALIGNED_SIZE(name_len);
        }