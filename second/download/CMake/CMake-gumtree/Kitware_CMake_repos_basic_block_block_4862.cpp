{
          streamclose(data->easy_conn, "Disconnected with pending data");
          stream_error = TRUE;
        }