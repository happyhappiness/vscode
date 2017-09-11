        public:
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
                const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);
