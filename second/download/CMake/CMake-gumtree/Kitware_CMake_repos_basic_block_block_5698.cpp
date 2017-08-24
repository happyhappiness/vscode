r(i = 3;i < length;i++) {
            switch(pointer[i]) {
            case CURL_NEW_ENV_VAR:
              infof(data, ", ");
              break;
            case CURL_NEW_ENV_VALUE:
              infof(data, " = ");
              break;
            default:
              infof(data, "%c", pointer[i]);
              break;
            }
          }