      } while (b != b_end);
    }
    this->size = dst - data;
    utils::Assert(size <= sa.size + sb.size, "bug in combine");
  }
};
/*! \brief try to do efficient prunning */
template<typename DType, typename RType>
struct WXQSummary : public WQSummary<DType, RType> {
