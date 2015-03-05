#include "PyDict.h"
#include "PyObject.h"
#include "PyType.h"
#include <vector>
#include <unordered_map>

using namespace std;

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

}

PyObject* PyDict::keys(vector<PyObject*>* args) {

}

PyObject* PyDict::values(vector<PyObject*>* args) {

}
