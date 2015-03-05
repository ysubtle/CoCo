#ifndef PYDICTITERATOR_H
#define	PYDICTITERATOR_H

#include "PyDict.h"
#include "PyType.h"
#include <unordered_map>

using namespace std;

class PyDictIterator : public PyObject {
public:
    PyDictIterator(PyObject* map);
    virtual ~PyDictIterator();

    PyType* getType();
    string toString();
protected:
	int index;
	unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual> map;

    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);
};

#endif	/* PYDICTITERATOR_H */