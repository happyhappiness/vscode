snprintf(p, sizeof(ftp_typecode) - 1, ";type=%c",
                   data->set.prefer_ascii ? 'a' : 'i');