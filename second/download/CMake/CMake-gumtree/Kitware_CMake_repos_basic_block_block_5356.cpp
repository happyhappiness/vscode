f(result) {
      connclose(conn, "SMB: failed to send setup message");
      return result;
    }