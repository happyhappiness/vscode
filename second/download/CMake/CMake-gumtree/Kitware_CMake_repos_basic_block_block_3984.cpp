result = Curl_client_chop_write(data->easy_conn,
                                        writebuf[i].type,
                                        writebuf[i].buf,
                                        writebuf[i].len)