/* 
 * File:   PyCallable.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 17, 2013, 12:21 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 */

#include "PyCallable.h"
#include "PyStr.h"
#include "PyException.h"

PyCallable::PyCallable() : PyObject() {
    dict["__call__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyCallable::__call__);
}

PyCallable::PyCallable(const PyCallable& orig) {
}

PyCallable::~PyCallable() {
}

string PyCallable::toString() {
    return "callable";
}

PyObject* PyCallable::__str__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    
    string s = "<built-in function " + toString() + ">";
    return new PyStr(s);
}

PyObject* PyCallable::__repr__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    
    return __str__(args);
}