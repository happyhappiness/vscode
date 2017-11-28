CommonPool *
CommonPool::Factory(unsigned char _class, CompositePoolNode::Pointer& compositeCopy)
{
    CommonPool *result = new CommonPool;

    switch (_class) {

    case 0:
        break;

    case 1:
        compositeCopy = new Aggregate;
        result->typeLabel = "1";
        break;

    case 2:
        result->typeLabel = "2";
        {
            DelayVector::Pointer temp = new DelayVector;
            compositeCopy = temp.getRaw();
            temp->push_back (new Aggregate);
            temp->push_back(new IndividualPool);
        }
        break;

    case 3:
        result->typeLabel = "3";
        {
            DelayVector::Pointer temp = new DelayVector;
            compositeCopy = temp.getRaw();
            temp->push_back (new Aggregate);
            temp->push_back (new ClassCNetPool);
            temp->push_back (new ClassCHostPool);
        }
        break;

    case 4:
        result->typeLabel = "4";
        {
            DelayVector::Pointer temp = new DelayVector;
            compositeCopy = temp.getRaw();
            temp->push_back (new Aggregate);
            temp->push_back (new ClassCNetPool);
            temp->push_back (new ClassCHostPool);
            temp->push_back (new DelayUser);
        }
        break;

    case 5:
        result->typeLabel = "5";
        compositeCopy = new DelayTagged;
        break;

    default:
        fatal ("unknown delay pool class");
        return NULL;
    };

    return result;
}