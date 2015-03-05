#include "PyDictIterator.h"
#include <string>
using namespace std;

PyDictIterator::PyDictIterator(unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>* map) {
    this->index = 0;
    map = map;
    it = map->begin();
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDictIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDictIterator::__next__);
}

PyDictIterator::~PyDictIterator() {

}

PyType* PyDictIterator::getType() {
	return PyTypes[PyDictKeyIteratorType];
}

string PyDictIterator::toString() {
	ostringstream s;

	s << "<dict_iterator object at " << this << ">";

	return s.str();
}

PyObject* PyDictIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    it = map->begin();
    return this;
}

PyObject* PyDictIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    if (it == map->end()) {
        msg << "Too far:";
        throw new PyException(PYSTOPITERATIONEXCEPTION, msg.str());
    }
    
    PyObject* value = it->first;
    it++;
    return value;
}