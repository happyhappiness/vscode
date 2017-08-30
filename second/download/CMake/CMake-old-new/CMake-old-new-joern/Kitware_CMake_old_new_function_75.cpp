static void kwsysProcessSetExitException(kwsysProcess* cp, int code)
{
  switch (code) {
    case STATUS_CONTROL_C_EXIT:
      KWSYSPE_CASE(Interrupt, "User interrupt");
      break;

    case STATUS_FLOAT_DENORMAL_OPERAND:
      KWSYSPE_CASE(Numerical, "Floating-point exception (denormal operand)");
      break;
    case STATUS_FLOAT_DIVIDE_BY_ZERO:
      KWSYSPE_CASE(Numerical, "Divide-by-zero");
      break;
    case STATUS_FLOAT_INEXACT_RESULT:
      KWSYSPE_CASE(Numerical, "Floating-point exception (inexact result)");
      break;
    case STATUS_FLOAT_INVALID_OPERATION:
      KWSYSPE_CASE(Numerical, "Invalid floating-point operation");
      break;
    case STATUS_FLOAT_OVERFLOW:
      KWSYSPE_CASE(Numerical, "Floating-point overflow");
      break;
    case STATUS_FLOAT_STACK_CHECK:
      KWSYSPE_CASE(Numerical, "Floating-point stack check failed");
      break;
    case STATUS_FLOAT_UNDERFLOW:
      KWSYSPE_CASE(Numerical, "Floating-point underflow");
      break;
#ifdef STATUS_FLOAT_MULTIPLE_FAULTS
    case STATUS_FLOAT_MULTIPLE_FAULTS:
      KWSYSPE_CASE(Numerical, "Floating-point exception (multiple faults)");
      break;
#endif
#ifdef STATUS_FLOAT_MULTIPLE_TRAPS
    case STATUS_FLOAT_MULTIPLE_TRAPS:
      KWSYSPE_CASE(Numerical, "Floating-point exception (multiple traps)");
      break;
#endif
    case STATUS_INTEGER_DIVIDE_BY_ZERO:
      KWSYSPE_CASE(Numerical, "Integer divide-by-zero");
      break;
    case STATUS_INTEGER_OVERFLOW:
      KWSYSPE_CASE(Numerical, "Integer overflow");
      break;

    case STATUS_DATATYPE_MISALIGNMENT:
      KWSYSPE_CASE(Fault, "Datatype misalignment");
      break;
    case STATUS_ACCESS_VIOLATION:
      KWSYSPE_CASE(Fault, "Access violation");
      break;
    case STATUS_IN_PAGE_ERROR:
      KWSYSPE_CASE(Fault, "In-page error");
      break;
    case STATUS_INVALID_HANDLE:
      KWSYSPE_CASE(Fault, "Invalid hanlde");
      break;
    case STATUS_NONCONTINUABLE_EXCEPTION:
      KWSYSPE_CASE(Fault, "Noncontinuable exception");
      break;
    case STATUS_INVALID_DISPOSITION:
      KWSYSPE_CASE(Fault, "Invalid disposition");
      break;
    case STATUS_ARRAY_BOUNDS_EXCEEDED:
      KWSYSPE_CASE(Fault, "Array bounds exceeded");
      break;
    case STATUS_STACK_OVERFLOW:
      KWSYSPE_CASE(Fault, "Stack overflow");
      break;

    case STATUS_ILLEGAL_INSTRUCTION:
      KWSYSPE_CASE(Illegal, "Illegal instruction");
      break;
    case STATUS_PRIVILEGED_INSTRUCTION:
      KWSYSPE_CASE(Illegal, "Privileged instruction");
      break;

    case STATUS_NO_MEMORY:
    default:
      cp->ExitException = kwsysProcess_Exception_Other;
      _snprintf(cp->ExitExceptionString, KWSYSPE_PIPE_BUFFER_SIZE,
                "Exit code 0x%x\n", code);
      break;
  }
}