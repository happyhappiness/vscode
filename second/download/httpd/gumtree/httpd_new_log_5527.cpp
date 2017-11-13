apr_file_printf(
                                                    outfile,
                                                    "%s %" APR_SIZE_T_FMT
                                                    " %" APR_SIZE_T_FMT
                                                    " %d %" APR_SIZE_T_FMT
                                                    " %" APR_TIME_T_FMT
                                                    " %" APR_TIME_T_FMT
                                                    " %" APR_TIME_T_FMT
                                                    " %" APR_TIME_T_FMT
                                                    " %d %d\n",
                                                    url,
                                                    round_up((apr_size_t)hinfo.size, round),
                                                    round_up(
                                                            disk_info.has_body ? (apr_size_t)dinfo.size
                                                                    : 0, round),
                                                    disk_info.status,
                                                    disk_info.entity_version,
                                                    disk_info.date,
                                                    disk_info.expire,
                                                    disk_info.request_time,
                                                    disk_info.response_time,
                                                    disk_info.has_body,
                                                    disk_info.header_only);