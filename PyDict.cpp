#include "PyDict.h"
#include "PyObject.h"
#include "PyType.h"
#include <vector>
#include <unordered_map>

using namespace std;

bool PyKeysEqual::operator() (const PyObject* key1, const PyObject* key2) const {
    vector<PyObject*> args;
    args.push_back(const_cast<PyObject*>(key2));
    PyBool* test = (PyBool*) const_cast<PyObject*>(key1)->callMethod("__eq__",&args);
    return test->getVal();
}

PyDict::PyDict() {
	unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual> map;
}

PyDict::~PyDict() {

}

PyType* PyDict::getType() {
	return PyTypes[PyDictType];
}

string PyDict::toString() {
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>::iterator it;
    ostringstream s;
    s << "{";
    it = map.begin();
    while (it!=map.end()) {
        s << it->first->toString() << ": " << it->second->toString();
        it++;
        if (it!=map.end())
            s << ", ";
    }
    s << "}";
    return s.str();
}

PyObject* PyDict::getVal(PyObject* key) {

}

void PyDict::setVal(PyObject* key, PyObject* val) {

}

PyObject* PyDict::__getitem__(vector<PyObject*>* args) {

}

PyObject* PyDict::__setitem__(vector<PyObject*>* args) {

}

PyObject* PyDict::__len__(vector<PyObject*>* args) {

}

PyObject* PyDict::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
    }

    return new PyDictIterator(map);
}

PyObject* PyDict::keys(vector<PyObject*>* args) {

}

PyObject* PyDict::values(vector<PyObject*>* args) {

}
