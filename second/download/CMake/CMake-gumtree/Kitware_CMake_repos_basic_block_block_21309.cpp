(membership) {
    case UV_JOIN_GROUP:
      optname = IP_ADD_MEMBERSHIP;
      break;
    case UV_LEAVE_GROUP:
      optname = IP_DROP_MEMBERSHIP;
      break;
    default:
      return UV_EINVAL;
  }