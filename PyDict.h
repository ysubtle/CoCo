#include "PyObject.h"
#include "PyType.h"
#include <vector>
#ifndef PYDICT_H
#define PYDICT_H

#include <unordered_map>
using namespace std;

class PyHash
{
public:
    std::size_t operator() (const PyObject* key) const;
};

std::size_t PyHash::operator() (const PyObject* key) const {
    vector<PyObject*> args;
    PyInt* hashVal = (PyInt*) const_cast<PyObject*>(key)->callMethod("__hash__",&args);
    return hashVal->getVal();
};

class PyKeysEqual
{
public:
    bool operator() (const PyObject* key1, const PyObject* key2) const;
};

class PyDict : public PyObject {
public:
    PyDict();
    virtual ~PyDict();
    PyType* getType();
    string toString();
    PyObject* getVal(PyObject* key);
    void setVal(PyObject* key, PyObject* val);
protected:
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual> map;
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>::iterator it;
    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __setitem__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* keys(vector<PyObject*>* args);
    virtual PyObject* values(vector<PyObject*>* args);
};

#endif  /* PYDICT_H */