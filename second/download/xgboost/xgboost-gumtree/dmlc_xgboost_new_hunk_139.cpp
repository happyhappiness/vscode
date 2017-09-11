    case kULong: return MPI::UNSIGNED_LONG;
    case kFloat: return MPI::FLOAT;
    case kDouble: return MPI::DOUBLE;
    case kLongLong: return MPI::LONG_LONG;
    case kULongLong: return MPI::UNSIGNED_LONG_LONG;
  }
  utils::Error("unknown mpi::DataType");
  return MPI::CHAR;
