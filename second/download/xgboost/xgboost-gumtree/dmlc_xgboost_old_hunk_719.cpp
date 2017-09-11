        public:
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0, "must specify group when constructing rank file");
                utils::Assert( gptr.back() == preds.size(), "EvalRanklist: group structure must match number of prediction");
