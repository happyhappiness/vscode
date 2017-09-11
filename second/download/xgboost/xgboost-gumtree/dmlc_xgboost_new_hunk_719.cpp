        public:
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0, "must specify group when constructing rank file");
                utils::Assert( gptr.back() == preds.size(), "EvalRanklist: group structure must match number of prediction");
