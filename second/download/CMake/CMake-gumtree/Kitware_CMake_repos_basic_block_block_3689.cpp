{
      CURLcode result = resolver_error(conn);
      destroy_async_data(&conn->async);
      return result;
    }