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

}

string PyDict::toString() {

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
