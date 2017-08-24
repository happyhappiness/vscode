f(conn->bits.type_set)
        snprintf(type, sizeof(type), ";type=%c",
                 data->set.prefer_ascii?'A':
                 (data->set.ftp_list_only?'D':'I'))