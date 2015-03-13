#include "PyDict.h"
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
    dict["__setitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__setitem__);
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__getitem__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__iter__);
    dict["keys"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::keys);
    dict["values"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::values);
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
	} else {
		return se->second;
	}
}

void PyDict::setVal(PyObject* key, PyObject* val) {
    pair<PyObject*, PyObject*> npair (key, val);
    map.insert(npair);
}

PyObject* PyDict::__str__(vector<PyObject*>* args) {
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>::iterator it;
    ostringstream s;
    s << "{";
    it = map.begin();
    while (it!=map.end()) {
        s << *it->first->callMethod("__repr__", args) << ": " << *it->second->callMethod("__repr__", args);
        it++;
        if (it!=map.end())
            s << ", ";
    }
    s << "}";
    return new PyStr(s.str());
}

PyObject* PyDict::__repr__(vector<PyObject*>* args) {
    return __str__(args);
}

PyObject* PyDict::__getitem__(vector<PyObject*>* args) {
    PyObject* PyKey = (PyObject*) (*args)[0];
    auto se = map.find(PyKey);
    if (se == map.end()) {
        cout << "Error, not found" << endl;
    } else {
        return se->second;
    }
}

PyObject* PyDict::__setitem__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 2) {
        msg << "TypeError expected 2 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }

    PyObject* key = (PyObject*) (*args)[0];
    PyObject* obj = (PyObject*) (*args)[1];

    pair<PyObject*, PyObject*> npair (key, obj);

    map.insert(npair);

    return new PyNone();
}

PyObject* PyDict::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    
    return new PyInt(map.size());
}

PyObject* PyDict::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);
    }

    return new PyDictIterator(&map);
}

PyObject* PyDict::keys(vector<PyObject*>* args) {
    vector<PyObject*>* vals = new vector<PyObject*>();
    
    for (auto kv : map) {
        vals->push_back(kv.first);
    }
    
    return new PyList(vals);
}

PyObject* PyDict::values(vector<PyObject*>* args) {
    vector<PyObject*>* vals = new vector<PyObject*>();
    
    for (auto kv : map) {
        vals->push_back(kv.second);
    }

    return new PyList(vals);
}
