{
            error = SELECT_ERROR;
            failf(data, "Proxy CONNECT aborted due to select/poll error");
            break;
          }