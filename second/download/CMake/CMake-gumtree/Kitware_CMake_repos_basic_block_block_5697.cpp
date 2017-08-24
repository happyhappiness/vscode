{
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