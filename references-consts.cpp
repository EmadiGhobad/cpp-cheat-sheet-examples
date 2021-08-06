#include <iostream>
#include <string>
using namespace std;

class Sample {

public:
    int nonConstField;
    const int constField;

    /* You have to initialize constant field in the constructor in this special way! */
    Sample(int constantInitialValue, int nonConstField): constField(constantInitialValue)
    {
        /* not possible to initialize like that, compile Error! */
        //constField = constantInitialValue;

        this->nonConstField = nonConstField;
    }

    /* callable just from not constant objects */
    void nonConstMethodIncrease()
    {
        nonConstField ++;
    }

    /* callable from constant/not constant objects */
    /*
            can do anything but will not
            modify any data members
    */
    void constMethodPrint() const
    {
        /* can not change fields in const method of class, compile error! */
        //nonConstField ++;

        cout << "nonConstField: " << nonConstField << " constField: " << constField << endl;
    }
};

/*
 * Remember that const applies to the item to its left
 * (or if there is no item to its left, the item to its right).
 */
void constValueSample()
{
    int value[] = { 0 , 1};
    /* two definitions are the same */
    int const * constValue1 = &value[0];
    const int * constValue2 = &value[1];

    cout << "constValue1: " << constValue1 << "constValue2: " << constValue2 << endl;
    /* changing the pointer is okay! */
    constValue1 ++;
    constValue2 --;
    cout << "constValue1: " << constValue1 << "constValue2: " << constValue2 << endl;

    /* Not possible to change the value, compile Error! */
    //    *constValue1 = 0;
    //    *constValue2 = 0;

}
void constPointerSample()
{
    int value[] = { 0 , 1};
    int * const constValue1 = &value[0];
    int * const constValue2 = &value[1];
    /* changing the value is okay! */
    cout << "constValue1: " << constValue1 << " constValue2: " << constValue2 << endl;
    *constValue1 = 1;
    *constValue2 = 0;
    cout << "constValue1: " << constValue1 << " constValue2: " << constValue2 << endl;

    /* Not possible to change the pointer, compile Error! */
    //    constValue1 ++;
    //    constValue2 --;
}
void constBothPointerValueSample()
{
    int value[] = { 0 , 1};
    int const * const constValue1 = &value[0];
    int const * const constValue2 = &value[1];
    cout << "constValue1: " << constValue1 << " constValue2: " << constValue2 << endl;

    /* Not possible to change the value, compile Error! */
    //    *constValue1 = 1;
    //    *constValue2 = 0;

    /* Not possible to change the pointer, compile Error! */
    //    constValue1 ++;
    //    constValue2 --;
}

/* The reference could NOT be NULL or reassign during the function. Safer than 'Sample *'! */
void canChangeValueByReference(Sample &object)
{
    object.nonConstMethodIncrease();
}

/* The reference could be NULL and reassign during the function. Use it if it is really required */
void canChangeValueByReference(Sample *object)
{
    object->nonConstMethodIncrease();
}

/* The reference could NOT be NULL or reassign during the function */
void canNotChangeValueByReference(const Sample &constSample){
    /* no object updating is allowed */
    //constSample.nonConstField = 10;

    /* no reassigning is allowed */
    //constSample ++;
}

/* The reference could be NULL and reassign during the function */
void canNotChangeValueByReference(const Sample * constSample){
    /* no object updating is allowed */
    //constSample->nonConstField = 10;

    /* reassigning is allowed */
    constSample ++;
}


int main() {
    Sample constSample(10, 20);
    /* can not change constant field of class, compile error! */
    //constSample.constField = 10;

    /* define constant Object of class */
    Sample  const *p = &constSample;

    /* just calling const-methods is possible */
    p->constMethodPrint();

    /* calling non-const-method or changing public fields is forbidden, compile Error! */
    //pointer->nonConstMethodIncrease();
    //pointer->nonConstField = 0;

    const Sample& constReference = (Sample &) constSample;
    canNotChangeValueByReference(constReference);

    const Sample * constPointer = &constSample;
    canNotChangeValueByReference(constPointer);


    Sample& reference = (Sample &) constSample;
    canChangeValueByReference(reference);

    Sample * pointer = &constSample;
    canChangeValueByReference(pointer);

    return 0;
}

