#include "PyObject.h"
#include "PyType.h"
#include <vector>
#include <unordered_map>
using namespace std;

class PyHash
{
public:
    std::size_t operator() (const PyObject* key) const;
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
    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __setitem__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* keys(vector<PyObject*>* args);
    virtual PyObject* values(vector<PyObject*>* args);
};