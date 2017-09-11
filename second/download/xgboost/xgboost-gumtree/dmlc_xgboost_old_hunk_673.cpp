            }
        };

        /*! \brief Area under curve, for both classification and rank */
        struct EvalAuc : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
