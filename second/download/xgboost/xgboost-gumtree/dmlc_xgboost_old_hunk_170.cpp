    case kULong: return MPI::UNSIGNED_LONG;
    case kFloat: return MPI::FLOAT;
    case kDouble: return MPI::DOUBLE;
  }
  utils::Error("unknown mpi::DataType");
  return MPI::CHAR;
