#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
	struct MyTryPass : public FunctionPass {
		static char ID;
		MyTryPass() : FunctionPass(ID) {}

		void deal_call(CallInst * inst)
		{
			if(inst->getOpcode() == Instruction::Call)
			{
				errs() << "called function is: " << inst->getCalledFunction()->getName() << "\n";
				errs() << "number of args is: " << inst->getNumArgOperands() << "\n";

				// add log statement after this callee
			}
		}

		bool runOnFunction(Function &F) override
		{
			errs() << "now pass is: Mypass\n";
			// function info (name and argument)
			errs() << F.getName() << "\t"
					<< F.arg_size() << "\n";
			//print all callee
			for(Function::iterator bbIter = F.begin(); bbIter != F.end(); bbIter++)
			{
				for(BasicBlock::iterator instIter = bbIter->begin(); instIter != bbIter->end(); instIter++)
				{
					errs() << instIter->getOpcodeName() << '\n';
					if(instIter->getOpcode() == Instruction::Call)
					{
						// errs() << instIter->getOpcode();
						// CallInst* callee = dyn_cast<CallInst>(instIter);
						deal_call(dyn_cast<CallInst>(instIter));
					}
					// else if(instIter->getOpcode() == Instruction::Add)
					// {
					// 	errs() << instIter->getOpcode();
					// }
				}
			}

			return false;
		}



	};//end of structure

}// end of namespace


char MyTryPass::ID = 0;
static RegisterPass<MyTryPass> X("mypass", "print function and call instruction info");
