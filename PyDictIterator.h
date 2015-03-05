#ifndef PYDICTITERATOR_H
#define	PYDICTITERATOR_H

#include "PyType.h"

using namespace std;

class PyDictIterator : public PyObject {
public:
    PyDictIterator();
    virtual ~PyDictIterator();

    PyType* getType();
    string toString();
protected:
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);


};

#endif	/* PYCITITERATOR_H */