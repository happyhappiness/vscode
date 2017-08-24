h(field->just)
        {
        case JUSTIFY_LEFT:
          break;
        case JUSTIFY_CENTER:
          col = (field->cols - len)/2;
          break;
        case JUSTIFY_RIGHT:
          col = field->cols - len;
          break;
        default:
          break;
        }