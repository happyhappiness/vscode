                BinaryLinearSampler binary_linear_sampler;
                IPairSampler *sampler_;
            };

            template<typename T1, typename T2, typename T3>
            class Triple{
            public:
                T1 f1_;
                T2 f2_;
                T3 f3_;
                Triple(T1 f1, T2 f2, T3 f3) :f1_(f1), f2_(f2), f3_(f3){

                }
            };

            template<typename T1, typename T2, typename T3, typename T4>
            class Quadruple{
            public:
                T1 f1_;
                T2 f2_;
                T3 f3_;
                T4 f4_;
                Quadruple(T1 f1, T2 f2, T3 f3, T4 f4) :f1_(f1), f2_(f2), f3_(f3), f4_(f4){

                }
            };

            bool Triplef1Comparer(const Triple<float, float, int> &a, const Triple<float, float, int> &b){
                return a.f1_ > b.f1_;
            }


        }
    }


    

}
#endif
