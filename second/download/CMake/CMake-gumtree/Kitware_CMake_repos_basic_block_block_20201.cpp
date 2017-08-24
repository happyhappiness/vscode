(info->FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        dirent->d_type = UV__DT_LINK