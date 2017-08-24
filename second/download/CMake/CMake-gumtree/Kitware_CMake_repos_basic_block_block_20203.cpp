(WideCharToMultiByte(CP_UTF8,
                              0,
                              &info->FileName[0],
                              wchar_len,
                              &dirent->d_name[0],
                              utf8_len,
                              NULL,
                              NULL) == 0)
        goto win32_error;