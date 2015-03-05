#include "PyDict.h"
#include "PyObject.h"
#include "PyType.h"
#include "PyInt.h"
#include "PyBool.h"
#include "PyNone.h"
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

bool PyKeysEqual::operator() (const PyObject* key1, const PyObject* key2) const {
    vector<PyObject*> args;
    args.push_back(const_cast<PyObject*>(key2));
    PyBool* test = (PyBool*) const_cast<PyObject*>(key1)->callMethod("__eq__",&args);
    return test->getVal();
}

std::size_t PyHash::operator() (const PyObject* key) const {
    vector<PyObject*> args;
    PyInt* hashVal = (PyInt*) const_cast<PyObject*>(key)->callMethod("__hash__",&args);
    return hashVal->getVal();
};


PyDict::PyDict() {
	unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual> map; //constructor for PyDict
}

PyDict::~PyDict() {
	// free memory
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
	auto se = map.find(key);   //auto infers type
	if (se == map.end()) {
		cout << "Error, not found" << endl;
		return se->second;
	} else {
		return se->second;
	}
}

void PyDict::setVal(PyObject* key, PyObject* val) {
    pair<PyObject*, PyObject*> npair (key, val);
    map.insert(npair);
}

PyObject* PyDict::__getitem__(vector<PyObject*>* args) {
    PyObject* PyKey = (PyObject*) (*args)[0];
    auto se = map.find(PyKey);
    return se->second;
}

PyObject* PyDict::__setitem__(vector<PyObject*>* args) {
     PyObject* PyKey = (PyObject*) (*args)[0];
     PyObject* PyObj = (PyObject*) (*args)[1];
     pair<PyObject*, PyObject*> npair (PyKey, PyObj);
     map.insert(npair);
     return new PyNone();
}

PyObject* PyDict::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyInt(map.size());
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
